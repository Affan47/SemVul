array_write_short()
{
  fprintf(out, "  ; array_write_short()\n");

  if (stack == 0)
  {

    fprintf(out, "  mov [%s+%s*2], %s\n", REG_STACK(reg-3), REG_STACK(reg-2), REG_STACK16(reg-1));
    reg -= 3;
  }
    else
  if (stack == 1)
  {
    fprintf(out, "  pop ebx\n");

    fprintf(out, "  mov [%s+%s*2], bx\n", REG_STACK(reg-2), REG_STACK(reg-1));
    stack -= 1;
    reg -= 2;
  }
    else
  if (stack == 2)
  {
    fprintf(out, "  pop ebx\n");
    fprintf(out, "  pop edi\n");

    fprintf(out, "  mov [edi+%s*2], bx\n", REG_STACK(reg-1));
    stack -= 2;
    reg -= 1;
  }
    else
  {
    fprintf(out, "  pop ebx\n");
    fprintf(out, "  pop esi\n");
    fprintf(out, "  pop edi\n");
    fprintf(out, "  sal esi, 1\n");
    fprintf(out, "  add edi, esi\n");
    fprintf(out, "  mov [esi], bx\n");
    stack -= 3;
  }

  return 0;
}
