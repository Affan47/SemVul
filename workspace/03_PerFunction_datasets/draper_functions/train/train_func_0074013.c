pvt_read(posn_status* posn_status)
{
  waypoint* wpt = waypt_new();
  GPS_PPvt_Data pvt = GPS_Pvt_New();

  if (GPS_Command_Pvt_Get(&pvt_fd, &pvt)) {
    pvt2wpt(pvt, wpt);
    GPS_Pvt_Del(&pvt);

    wpt->shortname = xstrdup("Position");

    if (gps_errno && posn_status) {
      posn_status->request_terminate = 1;
    }

    return wpt;
  }


  if (gps_errno) {
    fatal(MYNAME ": Fatal error reading position.\n");
  }

  waypt_free(wpt);
  GPS_Pvt_Del(&pvt);

  return NULL;
}
