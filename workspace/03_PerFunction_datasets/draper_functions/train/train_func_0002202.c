connect_fd (struct scanner *s)
{
  SANE_Status ret = SANE_STATUS_GOOD;
  int buffer_size = s->buffer_size;

  DBG (10, "connect_fd: start\n");

  if(s->fd > -1){
    DBG (5, "connect_fd: already open\n");
    ret = SANE_STATUS_GOOD;
  }
  else {
    ret = sanei_scsi_open_extended (s->device_name, &(s->fd), sense_handler,
      s, &s->buffer_size);
    if(!ret && buffer_size != s->buffer_size){
      DBG (5, "connect_fd: cannot get requested buffer size (%d/%d)\n",
        buffer_size, s->buffer_size);
    }
    else{
      DBG (15, "connect_fd: opened SCSI device\n");
    }
  }

  DBG (10, "connect_fd: finish %d\n", ret);

  return ret;
}
