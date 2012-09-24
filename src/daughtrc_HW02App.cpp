#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "Resources.h"
#include "Shape.h"
#include "daughtrc_HW02.h"
#include "Rectangle.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class daughtrc_HW02App : public AppBasic {
  public:

	//methods
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings(Settings* settings);
	void drawRectangle(uint8_t* pixels, rectangle* rectangle);
	static void clear(uint8_t* pixels);

  private:
	static const int kAppWidth=800;
	static const int kAppHeight=600;
	static const int kSurfaceSize=1024;

	//variables
	Surface* mySurface_;
	uint8_t* myPixels_;
	rectangle* rectangle_;

};

//set window size
void daughtrc_HW02App::prepareSettings(Settings* settings)
{
	settings->setWindowSize(kAppWidth,kAppHeight);
	settings->setResizable(false);
}

void daughtrc_HW02App::drawRectangle(uint8_t* pixels, rectangle* rectangle)
{
	for (int y = 0; y < kAppWidth; y++) {
		for (int x = 0; x < kAppHeight; x++) {
			if (x >= rectangle->x1 && x <= (rectangle->x1 + rectangle->width) &&
				y >= rectangle->y1 && y <= (rectangle->y1 + rectangle->height)) {
					int index = 3*(x+y*kAppWidth);
					pixels[index] = rectangle->color.r;
					pixels[index+1] = rectangle->color.g;
					pixels[index+2] = rectangle->color.b;
			}
		}
	}
}

void daughtrc_HW02App::setup()
{
	//initialize mySurface_
	mySurface_ = new Surface(kSurfaceSize,kSurfaceSize,true);
	myPixels_ = (*mySurface_).getData();
	clear(myPixels_);

	rectangle_ = new rectangle();
	rectangle_->set(100,100,100,100,Color8u(0,0,0));
	drawRectangle(myPixels_, rectangle_);

}

void daughtrc_HW02App::clear(uint8_t* pixels){
	Color c = Color(250.0,250.0,250.0);
	for(int y = 0; y < kSurfaceSize; y++){
		for(int x = 0; x < kSurfaceSize; x++){
			int index = 3*(x + y*kAppWidth);
			pixels[index] = c.r;
			pixels[index+1] = c.g;
			pixels[index+2] = c.b;
		}
	}
}

void daughtrc_HW02App::mouseDown( MouseEvent event )
{
}

void daughtrc_HW02App::update()
{
}

void daughtrc_HW02App::draw()
{
	// clear out the window with white
	//gl::clear( Color( 250.0, 250.0, 250.0 ) ); 
	gl::draw(*mySurface_);
}

CINDER_APP_BASIC( daughtrc_HW02App, RendererGl )