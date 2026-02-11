push_integer(int32_t n)
{
  fprintf(out, "  ; push_integer(%d)\n", n);

  if (reg < REG_MAX)
  {
    fprintf(out, "  mov %s, %d\n", REG_STACK(reg++), n);
  }
    else
  {
    fprintf(out, "  push %d\n", n);
    stack++;
  }

  return 0;
}
