termread(char* ibuf, int size)
{
  if (is_file) {
    return gbfgets(ibuf, size, magfile_h);
  } else {
    int rc;
    rc = gbser_read_line(serial_handle, ibuf, size, 2000, 0x0a, 0x0d);
    if (rc != gbser_OK) {
      fatal(MYNAME ": Read error\n");
    }
    return ibuf;
  }
}
