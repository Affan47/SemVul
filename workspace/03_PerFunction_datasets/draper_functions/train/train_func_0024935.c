skytraq_set_location(void)
{
  double lat, lng;
  int i;
  gbuint8 MSG_SET_LOCATION[17] = { 0x36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  gbuint8 MSG_GET_LOCATION = 0x35;

  db(3, MYNAME ": set_location='%s'\n", opt_set_location);

  sscanf(opt_set_location, "%lf:%lf", &lat, &lng);
  le_write_double(&MSG_SET_LOCATION[1], lat);
  le_write_double(&MSG_SET_LOCATION[9], lng);
  for (i=0; i<sizeof MSG_SET_LOCATION; i++) {
    db(3, "%02x ", MSG_SET_LOCATION[i]);
  }
  db(3, "\n");
  if (skytraq_wr_msg_verify((gbuint8*)&MSG_SET_LOCATION, sizeof(MSG_SET_LOCATION)) != res_OK) {
    fatal(MYNAME ": cannot set new location\n");
  }
  {
    char buf[32];
    skytraq_wr_msg_verify(&MSG_GET_LOCATION, 1);
    skytraq_rd_msg(buf, 32);
  }
}
