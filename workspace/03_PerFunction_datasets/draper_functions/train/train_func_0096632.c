wr_char(int c)
{
  int rc;
  db(4, "Sending: %02x '%c'\n", (unsigned)c, isprint(c) ? c : '.');
  if (rc = gbser_writec(serial_handle, c), gbser_OK != rc) {
    fatal(MYNAME ": Write error (%d)\n", rc);
  }
}
