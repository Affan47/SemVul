updateBackground(unsigned long oldbg_)
{
  MSWidgetCommon::updateBackground(oldbg_);
  if (mapped()==MSTrue) redraw();
}
