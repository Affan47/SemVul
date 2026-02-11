spi_read(int port)
{
  if (port != 0) { return -1; }

  fprintf(out, "  call #_read_spi\n");
  push_reg("r15");

  need_read_spi = 1;

  return 0;
}
