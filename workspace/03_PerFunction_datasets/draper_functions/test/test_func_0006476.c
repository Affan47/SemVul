getPoint(size_t idx, Float32& x, Float32& y)
{
  x=0.0;
  y=0.0;
  OFCondition result = EC_IllegalCall;
  if ((idx*2+1)<graphicData.getVM())
  {
    result = graphicData.getFloat32(x, 2*idx);
    if (result==EC_Normal) result = graphicData.getFloat32(y, 2*idx+1);
  }
  return result;
}
