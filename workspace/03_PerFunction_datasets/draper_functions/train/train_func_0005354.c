convert_datum(const waypoint* wpt, double* dest_lat, double* dest_lon)
{
  double alt;

  if (datum_index == DATUM_WGS84) {
    *dest_lat = wpt->latitude;
    *dest_lon = wpt->longitude;
  } else GPS_Math_WGS84_To_Known_Datum_M(wpt->latitude, wpt->longitude, 0.0,
                                           dest_lat, dest_lon, &alt, datum_index);
}
