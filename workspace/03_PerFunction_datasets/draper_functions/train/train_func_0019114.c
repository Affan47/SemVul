gusb_cmd_get(garmin_usb_packet* ibuf, size_t sz)
{
  int rv;
  unsigned char* buf = (unsigned char*) &ibuf->dbuf;
  int orig_receive_state;
  unsigned short pkt_id;
top:
  orig_receive_state = receive_state;
  switch (receive_state) {
  case rs_fromintr:
    rv = gusb_llops->llop_get_intr(ibuf, sz);
    break;
  case rs_frombulk:
    rv = gusb_llops->llop_get_bulk(ibuf, sz);
    break;
  default:
    fatal("Unknown receiver state %d\n", receive_state);
  }

  pkt_id = le_read16(&ibuf->gusb_pkt.pkt_id);
  if (gps_show_bytes) {
    int i;
    const char* m1, *m2;
    unsigned short pkttype = le_read16(&ibuf->gusb_pkt.databuf[0]);

    GPS_Diag("RX (%s) [%d]:",
             receive_state == rs_fromintr ? "intr" : "bulk", rv);

    for (i=0; i<rv; i++) {
      if (DEBUG_THRESH) {
        GPS_Diag("[...]");
        break;
      }
      GPS_Diag("%02x ", buf[i]);
    }

    for (i=0; i<rv; i++) {
      if (DEBUG_THRESH) {
        GPS_Diag("[...]");
        break;
      }
      GPS_Diag("%c", isalnum(buf[i])? buf[i] : '.');
    }

    m1 = Get_Pkt_Type(pkt_id, pkttype, &m2);
    if ((rv == 0)  && (receive_state == rs_frombulk)) {
      m1= "RET2INTR";
      m2=NULL;
    };
    GPS_Diag("(%-8s%s)\n", m1, m2 ? m2 : "");
  }


  if ((rv > 0) && (pkt_id == GUSB_REQUEST_BULK)) {
    receive_state = rs_frombulk;
    goto top;
  }


  if ((receive_state == rs_frombulk) && (rv <= 0)) {
    receive_state = rs_fromintr;
  }

  return rv;
}
