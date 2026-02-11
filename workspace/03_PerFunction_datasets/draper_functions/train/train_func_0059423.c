updateForeground(unsigned long oldfg_)
{
  MSWidgetOutput::updateForeground(oldfg_);
  textMSGC().foreground(foreground());
  if (showState() != ShowPixmap) drawLabel();
  if (showState() != ShowLabel) drawPixmap();
}
