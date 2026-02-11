computeDecorPixelWidth(void)
{
  unsigned width = 0;
  if (buttonState(UpDownArrows) == MSTrue)
  {
    width = computeArrowPixelWidth();
    if (comboOrTextButton() == MSTrue)
      width += computeButtonPixelWidth() + buttonSpacing();
  }
  else if(comboOrTextButton() == MSTrue) width = computeButtonPixelWidth();

  return width;
}
