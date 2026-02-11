mul_integer()
{
int n;
int saved_registers;

  saved_registers = reg;

  if(saved_registers != 2)
  {
    for (n = 0; n < reg; n++)
    {
      fprintf(out, "  push r%d\n", REG_STACK(n));
    }
  }

  if (stack == 0)
  {
    if(saved_registers != 2)
    {
      fprintf(out, "  mov r%d, r5\n", REG_STACK(reg-1));
      fprintf(out, "  mov r%d, r4\n", REG_STACK(reg-2));
    }
    fprintf(out, "  call #_mul_integers\n");
    reg--;
  }
    else
  if (stack == 1)
  {
    fprintf(out, "  mov r15, r5\n");
    fprintf(out, "  mov r%d, r4\n", REG_STACK(reg-1));
    fprintf(out, "  call #_mul_integers\n");
    stack--;
  }
    else
  {
    fprintf(out, "  mov r15, r5\n");
    fprintf(out, "  mov @SP, r4\n");
    fprintf(out, "  call #_mul_integers\n");
  }

  if(saved_registers != 2)
  {
    for (n = saved_registers-1; n >= 0; n--)
    {
      fprintf(out, "  pop r%d\n", REG_STACK(n));
    }
  }

  need_mul_integers = 1;

  return 0;
}
