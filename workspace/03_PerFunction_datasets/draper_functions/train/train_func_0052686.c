jtagmkI_send(PROGRAMMER * pgm, unsigned char * data, size_t len)
{
  unsigned char *buf;

  if (verbose >= 3)
    fprintf(stderr, "\n%s: jtagmkI_send(): sending %u bytes\n",
	    progname, (unsigned int)len);

  if ((buf = malloc(len + 2)) == NULL)
    {
      fprintf(stderr, "%s: jtagmkI_send(): out of memory",
	      progname);
      exit(1);
    }

  memcpy(buf, data, len);
  buf[len] = ' ';
  buf[len + 1] = ' ';

  if (serial_send(&pgm->fd, buf, len + 2) != 0) {
    fprintf(stderr,
	    "%s: jtagmkI_send(): failed to send command to serial port\n",
	    progname);
    exit(1);
  }

  free(buf);

  return 0;
}
