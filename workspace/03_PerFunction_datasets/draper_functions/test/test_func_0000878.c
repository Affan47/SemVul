spi_send(int port)
{
  if (port != 0) { return -1; }

  char dst[16];
  pop_reg(dst);

  fprintf(out, "  mov.b %s, r15\n", dst);
  fprintf(out, "  call #_read_spi\n");
  push_reg("r15");

  need_read_spi = 1;

  return 0;
}
