skytraq_probe(void)
{
  int baud_rates[] = { 9600, 230400, 115200, 57600, 4800, 19200, 38400 };
  int baud_rates_count = sizeof(baud_rates)/sizeof(baud_rates[0]);
  int initbaud = atoi(opt_initbaud);
  gbuint8 MSG_QUERY_SOFTWARE_VERSION[2] = { 0x02, 0x01 };
  struct {
    gbuint8 id;
    gbuint8 sw_type;
    gbuint8 kernel_ver[4];
    gbuint8 odm_ver[4];
    gbuint8 revision[4];
  } MSG_SOFTWARE_VERSION;
  int i, rc;


  if (initbaud > 0) {
    baud_rates[0] = initbaud;
    baud_rates_count = 1;
  }

  for (i = 0; i < baud_rates_count; i++) {
    db(1, MYNAME ": Probing SkyTraq Venus at %ibaud...\n", baud_rates[i]);

    rd_drain();
    if ((rc = gbser_set_speed(serial_handle, baud_rates[i])) != gbser_OK) {
      db(1, MYNAME ": Set baud rate to %d failed (%d), retrying...\n", baud_rates[i], rc);
      if ((rc = gbser_set_speed(serial_handle, baud_rates[i])) != gbser_OK) {
        db(1, MYNAME ": Set baud rate to %d failed (%d)\n", baud_rates[i], rc);
        continue;
      }
    }

    gb_sleep(50);

    skytraq_wr_msg(MSG_QUERY_SOFTWARE_VERSION,
                   sizeof(MSG_QUERY_SOFTWARE_VERSION));
    if ((rc = skytraq_expect_ack(0x02)) != res_OK) {
      db(2, "Didn't receive ACK (%d), retrying...\n", rc);
      skytraq_wr_msg(MSG_QUERY_SOFTWARE_VERSION,
                     sizeof(MSG_QUERY_SOFTWARE_VERSION));
      if ((rc = skytraq_expect_ack(0x02)) != res_OK) {
        db(2, "Didn't receive ACK (%d)\n", rc);
        continue;
      }
    }


    rc = skytraq_expect_msg(0x80, (gbuint8*)&MSG_SOFTWARE_VERSION, sizeof(MSG_SOFTWARE_VERSION));
    if (rc < (int)sizeof(MSG_SOFTWARE_VERSION)) {
      db(2, "Didn't receive expected reply (%d)\n", rc);
    } else {
      db(1, MYNAME ": Venus device found: Kernel version = %i.%i.%i, ODM version = %i.%i.%i, "\
         "revision (Y/M/D) = %02i/%02i/%02i\n",
         MSG_SOFTWARE_VERSION.kernel_ver[1], MSG_SOFTWARE_VERSION.kernel_ver[2],
         MSG_SOFTWARE_VERSION.kernel_ver[3],
         MSG_SOFTWARE_VERSION.odm_ver[1], MSG_SOFTWARE_VERSION.odm_ver[2],
         MSG_SOFTWARE_VERSION.odm_ver[3],
         MSG_SOFTWARE_VERSION.revision[1], MSG_SOFTWARE_VERSION.revision[2],
         MSG_SOFTWARE_VERSION.revision[3]);

      return baud_rates[i];
    }
  }

  return res_NOTFOUND;
}
