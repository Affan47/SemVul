Modified_value(int value,int modif)
{
  value+=modif;
  if (value<0)
  {
    value=0;
  }
  else if (value>255)
  {
    value=255;
  }
  return value;
}
