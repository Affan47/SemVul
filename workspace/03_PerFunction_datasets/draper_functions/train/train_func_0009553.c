method_start(int local_count, int max_stack, int param_count, const char *name)
{
  int i;

  if (method_count == 0)
  {
    fprintf(out, "  ret\n\n");
  }

  method_count++;

  fprintf(out, "; int %s(", name);
  for (i = 0; i < param_count; i++)
  {
    if (i != 0) { fprintf(out, ", "); }
    if (i < 26) { fprintf(out, "int %c", 'a' + i); }
  }
  fprintf(out, ");\n");

  fprintf(out, "global %s\n", name);
  fprintf(out, "%s:\n", name);

  fprintf(out, "  push ebx\n");
  fprintf(out, "  push esi\n");
  fprintf(out, "  push edi\n");
  fprintf(out, "  push ebp\n");
  fprintf(out, "  mov ebp, esp\n");

  if (local_count != 0)
  {
    fprintf(out, "  ; Allocate space for %d local variables\n", local_count);
    fprintf(out, "  sub esp, %d\n", local_count * 4);
  }


  if (param_count != 0)
  {
    fprintf(out, "  ; Copy %d parameters to local variables\n", param_count);

    for (i = 0; i < param_count; i++)
    {
      fprintf(out, "  mov eax, [ebp+%d]\n", (i * 4) + 8 + 12);
      fprintf(out, "  mov [ebp-%d], eax\n", LOCALS(i));
    }
  }
}
