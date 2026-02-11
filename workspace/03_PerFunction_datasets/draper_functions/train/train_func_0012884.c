updateBackground(unsigned long oldbg_)
{
  MSPrimitiveText::updateBackground(oldbg_);
  if(_leftArrow!=0) _leftArrow->background(background());
  if(_rightArrow!=0) _rightArrow->background(background());
  redraw();
}
