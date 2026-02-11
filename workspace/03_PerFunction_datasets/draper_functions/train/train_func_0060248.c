updateBackground(unsigned long oldbg_)
{
  if (slider()->background()==oldbg_)   slider()->background(background());
  if (valueWin()->background()==oldbg_) valueWin()->background(background());
  MSPrimitive::updateBackground(oldbg_);
  redraw();
}
