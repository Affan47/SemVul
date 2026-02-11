jtagmkI_program_disable(PROGRAMMER * pgm)
{
  unsigned char buf[1], resp[2];

  if (!PDATA(pgm)->prog_enabled)
    return 0;

  if (pgm->fd.ifd != -1) {
    buf[0] = CMD_LEAVE_PROGMODE;
    if (verbose >= 2)
      fprintf(stderr, "%s: jtagmkI_program_disable(): "
              "Sending leave progmode command: ",
              progname);
    jtagmkI_send(pgm, buf, 1);

    jtagmkI_recv(pgm, resp, 2);
    if (resp[0] != RESP_OK) {
      if (verbose >= 2)
        putc('\n', stderr);
      fprintf(stderr,
              "%s: jtagmkI_program_disable(): "
              "timeout/error communicating with programmer (resp %c)\n",
              progname, resp[0]);
      return -1;
    } else {
      if (verbose == 2)
        fprintf(stderr, "OK\n");
    }
  }
  PDATA(pgm)->prog_enabled = 0;

  return 0;
}
