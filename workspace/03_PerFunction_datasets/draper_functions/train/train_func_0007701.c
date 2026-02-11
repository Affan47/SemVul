nmea_release_wpt(waypoint* wpt)
{
  if (wpt && ((wpt->Q.next == NULL) || (wpt->Q.next == &wpt->Q))) {


    waypt_free(wpt);
  }
}
