jtagmkII_program_disable(PROGRAMMER * pgm)
{
  int status;
  unsigned char buf[1], *resp, c;

  if (!PDATA(pgm)->prog_enabled)
    return 0;

  buf[0] = CMND_LEAVE_PROGMODE;
  if (verbose >= 2)
    fprintf(stderr, "%s: jtagmkII_program_disable(): "
	    "Sending leave progmode command: ",
	    progname);
  jtagmkII_send(pgm, buf, 1);

  status = jtagmkII_recv(pgm, &resp);
  if (status <= 0) {
    if (verbose >= 2)
      putc('\n', stderr);
    fprintf(stderr,
	    "%s: jtagmkII_program_disable(): "
	    "timeout/error communicating with programmer (status %d)\n",
	    progname, status);
    return -1;
  }
  if (verbose >= 3) {
    putc('\n', stderr);
    jtagmkII_prmsg(pgm, resp, status);
  } else if (verbose == 2)
    fprintf(stderr, "0x%02x (%d bytes msg)\n", resp[0], status);
  c = resp[0];
  free(resp);
  if (c != RSP_OK) {
    fprintf(stderr,
	    "%s: jtagmkII_program_disable(): "
	    "bad response to leave progmode command: %s\n",
	    progname, jtagmkII_get_rc(c));
    return -1;
  }

  PDATA(pgm)->prog_enabled = 0;
  (void)jtagmkII_reset(pgm, 0x01);

  return 0;
}
