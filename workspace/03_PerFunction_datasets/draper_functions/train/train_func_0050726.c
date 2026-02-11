ausb11_bulk_read(ausb_dev_handle *ah, int ep,
			   char *bytes, int size,
			   int timeout){
  ausb11_extra *xh;

  DEBUGP(ah, "bulk read (ah=%p, ep=0x%x, bytes=%p, size=%d, timeout=%d\n",
         ah, ep, bytes, size, timeout);

  xh=(ausb11_extra*)ah->extraData;
  if (xh) {
    if (xh->ioError) {
      DEBUGP(ah, "Previous IO error, aborting transfer");
      return -1;
    }
    else {
      int transferred=0;
      int rv;


      ep |= LIBUSB_ENDPOINT_IN;

      rv=libusb_bulk_transfer(xh->uh, ep, (unsigned char*) bytes, size, &transferred, 0);
      if (rv) {
	DEBUGP(ah, "Error on libusb_bulk_transfer: %d", rv);
        xh->ioError=rv;
	return -1;
      }
      if (ah->pid!=0x100 &&
	  (bytes[0]==0x40 ||
	   bytes[0]==0x50)) {
	DEBUGP(ah, "interrupt event received via bulk-in\n");

      }

      return transferred;
    }
  }
  else
    return -1;
}
