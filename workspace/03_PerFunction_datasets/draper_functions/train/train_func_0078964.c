GPS_Math_UKOSMap_To_WGS84_C(char* map, double mE, double mN,
                                  double* lat, double* lon)
{
  double E;
  double N;
  double alat;
  double alon;
  double ht;

  if (!GPS_Math_UKOSNG_Map_To_EN(map,mE,mN,&E,&N)) {
    return 0;
  }

  GPS_Math_NGENToAiry1830LatLon(E,N,&alat,&alon);

  GPS_Math_Known_Datum_To_WGS84_C(alat,alon,0,lat,lon,&ht,86);

  return 1;
}
