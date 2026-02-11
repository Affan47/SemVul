butterfly_open(PROGRAMMER * pgm, char * port)
{
  strcpy(pgm->port, port);


  if(pgm->baudrate == 0) {
    pgm->baudrate = 19200;
  }
  if (serial_open(port, pgm->baudrate, &pgm->fd)==-1) {
    return -1;
  }


  butterfly_drain (pgm, 0);

  return 0;
}
