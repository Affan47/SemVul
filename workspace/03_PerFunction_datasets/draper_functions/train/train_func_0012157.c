insert_field_init_byte(char *name, int index, int value)
{
  if (value < -128 || value > 255) { return -1; }
  fprintf(out, "  mov.w #%d, &%s\n", (int8_t)value, name);
  return 0;
}
