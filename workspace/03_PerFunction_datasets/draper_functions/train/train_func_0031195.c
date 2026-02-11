ausb_open(rsct_usbdev_t *dev, int t) {
  ausb_dev_handle *ah=NULL;
  int rv;


  ah=malloc(sizeof *ah);
  if (ah==0) {
    DEBUGP(ah, "memory full\n");
    return 0;
  }
  memset(ah, 0, sizeof(*ah));

  ah->pid=dev->productId;
  ah->device=*dev;

  switch(t) {
  case 1:
#ifdef USE_USB1
    rv=ausb11_extend(ah);
#else
    rv=ausb1_extend(ah);
#endif
    break;

  case 2:
    DEBUGP(ah, "This type is no longer supported.\n");
    rv=-1;
    break;

  case 3:
#ifdef USE_USB1
    rv=ausb31_extend(ah);
#else
    rv=ausb3_extend(ah);
#endif
    break;

  default:
    DEBUGP(ah, "Invalid type %d\n", t);
    rv=-1;
    break;
  }

  if (rv) {
    DEBUGP(ah, "Could not extend as type %d (%d)\n", t, rv);
    free(ah);
    return 0;
  }

  return ah;
}
