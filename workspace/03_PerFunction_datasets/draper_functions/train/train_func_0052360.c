disconnect_fd (struct scanner *s)
{
  DBG (10, "disconnect_fd: start\n");

  if(s->fd > -1){
    DBG (15, "disconnecting usb device\n");
    sanei_usb_close (s->fd);
    s->fd = -1;
  }

  DBG (10, "disconnect_fd: finish\n");

  return SANE_STATUS_GOOD;
}
