getColorSelForeground () const
{
  static UT_RGBColor fgcolor (255, 255, 255);

  XAP_Frame * pFrame = 0;

  if ((pFrame = static_cast<XAP_Frame*>(getParentData())) != NULL)
    return pFrame->getColorSelForeground ();

  return fgcolor;
}
