push_array_length(const char *name, int field_id)
{
  fprintf(out, "  move.l (%s,a4), a0\n", name);

  if (reg < reg_max)
  {
    fprintf(out, "  move.l (-4,a0), d%d\n", REG_STACK(reg));
    reg++;
  }
    else
  {
    fprintf(out, "  move.l (-4,a0), d7\n");
    fprintf(out, "  move.l d7, -(SP)\n");
    stack++;
  }

  return 0;
}
