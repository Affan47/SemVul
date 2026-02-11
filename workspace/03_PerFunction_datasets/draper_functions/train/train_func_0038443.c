push_ref(char *name)
{
  if (reg < reg_max)
  {
    fprintf(out, "  mov #%s, w0\n", name);
    fprintf(out, "  mov [w0], w%d\n", REG_STACK(reg));
    reg++;
  }
    else
  {
    fprintf(out, "  mov #%s, w0\n", name);
    fprintf(out, "  push [w0]\n");
    stack++;
  }
  return 0;
}
