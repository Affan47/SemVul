setCircularShutter(Sint32 centerX, Sint32 centerY, Sint32 radius)
{
  OFCondition result=EC_Normal;
  char buf[80];

  sprintf(buf, "%ld\\%ld", (long)centerY, (long)centerX);
  result = centerOfCircularShutter.putString(buf);
  sprintf(buf, "%ld", (long)radius);
  if (EC_Normal==result) result = radiusOfCircularShutter.putString(buf);
  if ((EC_Normal==result)&&(shutterPresentationValue.getLength()==0))
      result = shutterPresentationValue.putUint16(0,0);
  if (EC_Normal==result)
  {
    useShutterCircular = OFTrue;
    if (useShutterBitmap) currentImageOverlaysValid = 1;
    useShutterBitmap = OFFalse;
  }
  return result;
}
