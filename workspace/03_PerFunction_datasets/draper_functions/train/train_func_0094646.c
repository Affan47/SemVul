array_read_int()
{
int index_reg;


  get_values_from_stack(&index_reg);
  get_ref_from_stack();
  fprintf(out, "  lsl.l #2, d%d\n", index_reg);


  if (reg < reg_max)
  {
    fprintf(out, "  move.l (d%d,a0), d%d\n", index_reg, REG_STACK(reg));
    reg++;
  }
    else
  {
    fprintf(out, "  move.l (d%d,a0), d7\n", index_reg);
    fprintf(out, "  move.l d7, -(SP)\n");
    stack++;
  }

  return 0;
}
