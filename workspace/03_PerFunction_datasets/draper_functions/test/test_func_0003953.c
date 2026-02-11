shift_left_integer(int count)
{
int n;

  if (stack != 0) { return -1; }

  if (count >= 8)
  {
    fprintf(out, "  swpb r%d\n", REG_STACK(reg-1));
    fprintf(out, "  and.w #0xff00, r%d\n", REG_STACK(reg-1));
    count = count - 8;
  }

  for (n = 0; n < count; n ++)
  {
    fprintf(out, "  rla.w r%d\n", REG_STACK(reg-1));
  }

  return 0;
}
