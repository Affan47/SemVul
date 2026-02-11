do_output(int sd)
{
  while(do_receive(sd, rbuf, MAXLINELEN) != NULL) {
    if (rbuf[0] == '.' && rbuf[1] == '\0') break;
    printf("> %s\n", rbuf);
  }
  fflush(stdout);
}
