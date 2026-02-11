shift_left_integer(int const_val)
{
  int i;

  fprintf(out, "; shift_left_integer (optimized)\n");
  POP_HI("result1");
  POP_LO("result0");

  for(i = 0; i < const_val; i++)
  {
    fprintf(out, "  lsl result0\n");
    fprintf(out, "  rol result1\n");
  }

  PUSH_LO("result0");
  PUSH_HI("result1");

  return 0;
}
