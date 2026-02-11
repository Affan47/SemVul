buspirate_open(struct programmer_t *pgm, char * port)
{

	if(pgm->baudrate == 0)
		pgm->baudrate = 115200;

	strcpy(pgm->port, port);
	if (serial_open(port, pgm->baudrate, &pgm->fd)==-1) {
	  return -1;
	}


	serial_drain(&pgm->fd, 0);

	return 0;
}
