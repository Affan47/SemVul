arrowColor(unsigned long pixel_)
{
  if(_leftArrow!=0) _leftArrow->arrowColor(pixel_);
  if(_rightArrow!=0) _rightArrow->arrowColor(pixel_);
}
