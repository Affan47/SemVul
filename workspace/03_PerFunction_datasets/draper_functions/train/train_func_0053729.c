ausb31_start_interrupt(ausb_dev_handle *ah, int ep) {
  ausb31_extra *xh;

  xh=(ausb31_extra*)ah->extraData;
  if (xh) {
    int rv;

    DEBUGP(ah, "Halting interrupt pipe.");
    rv=libusb_control_transfer(xh->uh,
			       0x02,
			       0x03,
			       0x00,
			       ep,
			       NULL, 0,
			       1200);
    if (rv<0) {
      DEBUGP(ah, "unable to halt interrupt pipe (%d=%s)\n",
	     errno, strerror(errno));
      return -1;
    }
    return 0;
  }
  else
    return -1;
}
