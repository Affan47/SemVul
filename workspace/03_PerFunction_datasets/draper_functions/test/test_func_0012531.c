return_integer(int local_count)
{
  if (stack > 0)
  {
    fprintf(out, "  move.l (SP)+, d7\n");
  }
    else
  {
    fprintf(out, "  move.l d%d, d7\n", REG_STACK(reg - 1));
  }

  if (local_count != 0) { fprintf(out, "  ulnk\n"); }
  fprintf(out, "  ret\n");
  return 0;
}
