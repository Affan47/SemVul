put_static(const char *name, int index)
{
  if (stack > 0)
  {
    fprintf(out, "  pop ebx\n");
    fprintf(out, "  mov [%s], ebx\n", name);
    stack--;
  }
    else
  {
    fprintf(out, "  mov [%s], %s\n", name, REG_STACK(reg - 1));
    reg--;
  }

  return 0;
}
