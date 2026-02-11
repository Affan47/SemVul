spi_isDataAvailable(int port)
{
  if (reg < reg_max)
  {
    fprintf(out, "  mov SPI1STAT, w%d\n", REG_STACK(reg));
    fprintf(out, "  and #(1<<SPIRBF), w%d\n", REG_STACK(reg));
    reg++;
  }
    else
  {
    fprintf(out, "  mov SPI1STAT, w0\n");
    fprintf(out, "  and #(1<<SPIRBF), w0\n");
    fprintf(out, "  push w0\n");
    stack++;
  }

  return 0;
}
