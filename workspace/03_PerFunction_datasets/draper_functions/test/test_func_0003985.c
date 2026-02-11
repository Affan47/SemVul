GPS_D302b_Get(GPS_PTrack* trk, UC* data)
{
  UC* p;
  uint32 t;
  double gps_temp;

  p=data;

  (*trk)->lat = GPS_Math_Semi_To_Deg(GPS_Util_Get_Int(p));
  p+=sizeof(int32);

  (*trk)->lon = GPS_Math_Semi_To_Deg(GPS_Util_Get_Int(p));
  p+=sizeof(int32);

  t = GPS_Util_Get_Uint(p);
  if (!t || t==0x7fffffff || t==0xffffffff) {
    (*trk)->Time=0;
  } else {
    (*trk)->Time = GPS_Math_Gtime_To_Utime((time_t)t);
  }
  p+=sizeof(uint32);

  (*trk)->alt = GPS_Util_Get_Float(p);
  p+=sizeof(float);

  (*trk)->dpth = GPS_Util_Get_Float(p);
  p+=sizeof(float);


  gps_temp = GPS_Util_Get_Float(p);
  if (gps_temp <= 1.0e24) {
    (*trk)->temperature_populated = 1;
    (*trk)->temperature = gps_temp;
  }

  p+=sizeof(float);

  (*trk)->tnew = *p;

  return;
}
