setRectShutter(Sint32 lv, Sint32 rv, Sint32 uh, Sint32 lh)
{
  OFCondition result=EC_Normal;
  char buf[80];

  sprintf(buf, "%ld", (long)lv);
  result = shutterLeftVerticalEdge.putString(buf);
  sprintf(buf, "%ld", (long)rv);
  if (EC_Normal==result) result = shutterRightVerticalEdge.putString(buf);
  sprintf(buf, "%ld", (long)uh);
  if (EC_Normal==result) result = shutterUpperHorizontalEdge.putString(buf);
  sprintf(buf, "%ld", (long)lh);
  if (EC_Normal==result) result = shutterLowerHorizontalEdge.putString(buf);
  if ((EC_Normal==result)&&(shutterPresentationValue.getLength()==0))
      result = shutterPresentationValue.putUint16(0,0);
  if (EC_Normal==result)
  {
    useShutterRectangular = OFTrue;
    if (useShutterBitmap) currentImageOverlaysValid = 1;
    useShutterBitmap = OFFalse;
  }
  return result;
}
