GPS_D105_Get(GPS_PWay* way, UC* s)
{
  UC* p;
  UC* q;

  p=s;

  (*way)->prot = 105;

  (*way)->lat = GPS_Math_Semi_To_Deg(GPS_Util_Get_Int(p));
  p+=sizeof(int32);

  (*way)->lon = GPS_Math_Semi_To_Deg(GPS_Util_Get_Int(p));
  p+=sizeof(int32);

  (*way)->smbl = GPS_Util_Get_Short(p);
  p+=sizeof(int16);

  q = (UC*)(*way)->wpt_ident;
  while ((*q++ = *p++));

  return;
}
