insert_static_field_define(const char *name, const char *type, int index)
{
  if (type[0] == '[') { need_tables = true; }
  fprintf(out, "%s equ ram_end-%d\n", name, (index + 2) * 2);

  return 0;
}
