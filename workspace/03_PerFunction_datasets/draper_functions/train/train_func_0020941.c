addPolyShutterVertex(Sint32 x, Sint32 y)
{
  if (verticesOfThePolygonalShutter.getLength()==0) return EC_IllegalCall;
  OFString aString;
  OFCondition result = verticesOfThePolygonalShutter.getOFStringArray(aString,OFTrue);
  if (result==EC_Normal)
  {
    char buf[80];
    sprintf(buf, "\\%ld\\%ld", (long)y, (long)x);
    aString += buf;
    result = verticesOfThePolygonalShutter.putOFStringArray(aString);
  }

  if (result==EC_Normal)
  {
    Sint32 xp0 = 0;
    Sint32 yp0 = 0;
    result = getPolyShutterVertex(0, xp0, yp0);
    if (result==EC_Normal)
    {
      if ((xp0==x)&&(yp0==y))
      {
        if (shutterPresentationValue.getLength()==0)
           result = shutterPresentationValue.putUint16(0,0);
        if (EC_Normal==result)
        {
          useShutterPolygonal = OFTrue;
          if (useShutterBitmap) currentImageOverlaysValid = 1;
          useShutterBitmap = OFFalse;
        }
      }
    }
  }
  return result;
}
