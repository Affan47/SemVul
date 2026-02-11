push_short(int16_t s)
{
  uint16_t value = s;

  if (reg < reg_max)
  {
    fprintf(out, "  mov #0x%02x, w%d\n", value, REG_STACK(reg));
    reg++;
  }
    else
  {
    fprintf(out, "  mov #0x%02x, w0\n", value);
    fprintf(out, "  push w0\n");
    stack++;
  }
  return 0;
}
