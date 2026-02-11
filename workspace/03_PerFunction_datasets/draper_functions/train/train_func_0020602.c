varpanel_highd (displayd * display)
{
  gboolean highd = false;

  if (display && GGOBI_IS_EXTENDED_DISPLAY (display)) {
    GGobiExtendedDisplayClass *klass;
    klass = GGOBI_EXTENDED_DISPLAY_GET_CLASS (display);
    if (klass->varpanel_highd)
      highd = klass->varpanel_highd (display);
  }

  return (highd);
}
