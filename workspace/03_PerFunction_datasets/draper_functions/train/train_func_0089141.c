GPS_D450_Send(UC* data, GPS_PWay way, int32* len)
{
  UC* p;
  int32 i;

  p = data;

  GPS_Util_Put_Short(p,(US) way->idx);
  p+=sizeof(int16);

  for (i=0; i<6; ++i) {
    *p++ = way->ident[i];
  }
  for (i=0; i<2; ++i) {
    *p++ = way->cc[i];
  }
  *p++ = way->wpt_class;

  GPS_Util_Put_Int(p,(int32)GPS_Math_Deg_To_Semi(way->lat));
  p+=sizeof(int32);
  GPS_Util_Put_Int(p,(int32)GPS_Math_Deg_To_Semi(way->lon));
  p+=sizeof(int32);

  GPS_Util_Put_Short(p,(US) way->alt);
  p+=sizeof(int16);

  for (i=0; i<24; ++i) {
    *p++ = way->city[i];
  }
  for (i=0; i<2; ++i) {
    *p++ = way->state[i];
  }
  for (i=0; i<30; ++i) {
    *p++ = way->name[i];
  }
  for (i=0; i<40; ++i) {
    *p++ = way->cmnt[i];
  }

  GPS_Util_Put_Float(p,way->dst);


  *len = 121;

  return;
}
