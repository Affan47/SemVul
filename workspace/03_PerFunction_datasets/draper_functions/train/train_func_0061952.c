ata_model (int device) {
  if(device == -1 || ioctl(device, HDIO_GET_IDENTITY, sbuff))
    return strdup(_("unknown"));
  else
    return strdup((char*) ((u16*)sbuff + 27));
}
