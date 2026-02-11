motionLoop(void)
{
  unsigned int mask=Button1Mask|Button2Mask;
  unsigned int keys=mask;
  int ix=0,iy=0;
  int rx=0,ry=0;
  int button_x,button_y;
  int newY,realY;
  int slideVal;
  Window root,child;

  freeze();
  _elevator->select();
  while (keys&mask)
   {
     XQueryPointer(display(),window(),&root,&child,&rx,&ry,&ix,&iy,&keys);
     button_y=iy;
     button_x=ix;


     if (button_x<sliderAreaRect().x()) button_x=sliderAreaRect().x();

     if (button_x>sliderAreaRect().x()+sliderAreaRect().width())
      button_x=sliderAreaRect().x()+sliderAreaRect().width();

     if (button_y<sliderAreaRect().y()) button_y=sliderAreaRect().y();

     if (button_y>sliderAreaRect().y()+sliderAreaRect().height())
      button_y=sliderAreaRect().y()+sliderAreaRect().height();


     newY=realY=button_y-_separation_y;

     if (newY<sliderAreaRect().y()) newY=sliderAreaRect().y();

     if (newY+_elevator->height()>sliderAreaRect().y()+sliderAreaRect().height())
      newY=sliderAreaRect().y()+sliderAreaRect().height()-_elevator->height();

     if (realY!=_initial_y)
      {
	slideVal=calcSliderValue(button_x,button_y);
	if (slideVal==value()) _changeType=NoChange;
	if (slideVal>=max()-viewSize())
	 {
	   slideVal=max()-viewSize();
	   newY=calcYValue(slideVal);
	 }
	int oldValue=value();
	_value=slideVal;
	moveElevator(_elevator->x(),newY);
	_initial_y=_elevator->y();
        if (oldValue!=_value) drag();
      }
   }
  _elevator->unselect();
  unfreeze();
}
