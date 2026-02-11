tp_ps2_disable_data (int fd)
{
  struct timeval tv;
  fd_set rfds;
  unsigned char status;
  byte cmd = PS2_DISABLE_DATA;


  FD_ZERO(&rfds);
  FD_SET (fd, &rfds);
  tv.tv_sec = 0;
  tv.tv_usec = 0;

  write(fd,&cmd,1);

  usleep (50000);

  while (select (fd+1, &rfds, NULL, NULL, &tv) == 1) {
    read (fd, &status, 1);
#if DEBUG_RESET
    gpm_report (GPM_PR_INFO,"PS/2 device disable data flush: %02X", status);
#endif
    FD_ZERO(&rfds);
    FD_SET (fd, &rfds);
    tv.tv_sec = 0;
    tv.tv_usec = 0;
  }

  if (status != PS2_ACK)
    gpm_report (GPM_PR_ERR,"Invalid ACK to disable stream command, got %02X",status);
}
