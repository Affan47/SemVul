kml_altitude_known(const waypoint* waypoint)
{
  if (waypoint->altitude == unknown_alt) {
    return 0;
  }


  if (fabs(waypoint->altitude) < .01) {
    return 0;
  }
  return 1;
}
