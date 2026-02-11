insert_field_init_short(char *name, int index, int value)
{
  if (value < -32768 || value > 65535) { return -1; }
  fprintf(out, "  mov.w #%d, &%s\n", value, name);
  return 0;
}
