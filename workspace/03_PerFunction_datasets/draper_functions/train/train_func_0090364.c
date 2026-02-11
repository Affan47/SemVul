print_conflict (int reg1, int reg2, void *contextp)
{
  struct print_context *context = (struct print_context *) contextp;
  int reg;


  if (! context->started)
    {
      fprintf (context->fp, " %d:", context->reg);
      context->started = 1;
    }


  if (reg1 == context->reg)
    reg = reg2;
  else if (reg2 == context->reg)
    reg = reg1;
  else
    abort ();


  fprintf (context->fp, " %d", reg);


  return 0;
}
