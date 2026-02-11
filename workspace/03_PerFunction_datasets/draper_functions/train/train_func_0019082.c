array_read_int(const char *name, int field_id)
{
  need_array_int_support = 1;

  if (stack > 0)
  {
    fprintf(out, "  lds ZL, %s + 0\n", name);
    fprintf(out, "  lds ZH, %s + 1\n", name);
    CALL("array_read_int2");
  }

  return 0;
}
