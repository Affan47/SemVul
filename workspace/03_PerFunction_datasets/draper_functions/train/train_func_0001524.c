jtagmkI_getparm(PROGRAMMER * pgm, unsigned char parm,
			    unsigned char * value)
{
  unsigned char buf[2], resp[3];

  if (verbose >= 2)
    fprintf(stderr, "%s: jtagmkI_getparm()\n", progname);

  buf[0] = CMD_GET_PARAM;
  buf[1] = parm;
  if (verbose >= 2)
    fprintf(stderr, "%s: jtagmkI_getparm(): "
	    "Sending get parameter command (parm 0x%02x): ",
	    progname, parm);
  jtagmkI_send(pgm, buf, 2);

  jtagmkI_recv(pgm, resp, 3);
  if (resp[0] != RESP_OK) {
    if (verbose >= 2)
      putc('\n', stderr);
    fprintf(stderr,
	    "%s: jtagmkI_getparm(): "
	    "timeout/error communicating with programmer (resp %c)\n",
	    progname, resp[0]);
    return -1;
  } else if (resp[2] != RESP_OK) {
    if (verbose >= 2)
      putc('\n', stderr);
    fprintf(stderr,
	    "%s: jtagmkI_getparm(): "
	    "unknown parameter 0x%02x\n",
	    progname, parm);
    return -1;
  } else {
    if (verbose == 2)
      fprintf(stderr, "OK, value 0x%02x\n", resp[1]);
  }

  *value = resp[1];

  return 0;
}
