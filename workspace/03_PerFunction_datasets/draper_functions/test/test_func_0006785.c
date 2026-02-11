GPS_D400_Get(GPS_PWay* way, UC* s)
{
  UC* p;
  int32 i;

  p=s;

  (*way)->prot = 400;
  for (i=0; i<6; ++i) {
    (*way)->ident[i] = *p++;
  }

  (*way)->lat = GPS_Math_Semi_To_Deg(GPS_Util_Get_Int(p));
  p+=sizeof(int32);

  (*way)->lon = GPS_Math_Semi_To_Deg(GPS_Util_Get_Int(p));
  p+=sizeof(int32);

  p+=sizeof(int32);

  for (i=0; i<40; ++i) {
    (*way)->cmnt[i] = *p++;
  }

  (*way)->dst=GPS_Util_Get_Float(p);


  return;
}
