ISDIJ(gribProduct ** grib, fortint * value) {
gribProduct * g = *grib;
  if( DEBUG2) printf("ISDIJ: value = %d\n", *value);
  if( !generalLatLonGrid(g) ) return 0;

  ISDI(grib,value);
  ISDJ(grib,value);
  return 0;
}
