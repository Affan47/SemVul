connect_fd (struct scanner *s)
{
  SANE_Status ret;
  int buffer_size = s->buffer_size;

  DBG (10, "connect_fd: start\n");

  if(s->fd > -1){
    DBG (5, "connect_fd: already open\n");
    ret = SANE_STATUS_GOOD;
  }
  else if (s->connection == CONNECTION_USB) {
    DBG (15, "connect_fd: opening USB device\n");
    ret = sanei_usb_open (s->device_name, &(s->fd));
    if(!ret){
      ret = sanei_usb_clear_halt(s->fd);
    }
  }
  else {
    DBG (15, "connect_fd: opening SCSI device\n");
    ret = sanei_scsi_open_extended (s->device_name, &(s->fd), sense_handler, s,
      &s->buffer_size);
    if(!ret && buffer_size != s->buffer_size){
      DBG (5, "connect_fd: cannot get requested buffer size (%d/%d)\n",
        buffer_size, s->buffer_size);
    }
  }

  if(ret == SANE_STATUS_GOOD){


    ret = wait_scanner(s);
    if (ret != SANE_STATUS_GOOD) {
      DBG (5, "connect_fd: could not wait_scanner\n");
      disconnect_fd(s);
    }

  }
  else{
    DBG (5, "connect_fd: could not open device: %d\n", ret);
  }

  DBG (10, "connect_fd: finish\n");

  return ret;
}
