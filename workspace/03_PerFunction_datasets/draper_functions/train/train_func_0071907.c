memory_read8()
{
  if (stack != 0)
  {
    fprintf(out, "  mov.w [SP-2], w0\n");
    fprintf(out, "  mov.b [w0], w0\n");
    fprintf(out, "  mov.b w0, [SP-2]\n");
  }
    else
  {
    fprintf(out, "  mov.b [w%d], w%d\n", REG_STACK(reg-1), REG_STACK(reg-1));
  }

  return 0;
}
