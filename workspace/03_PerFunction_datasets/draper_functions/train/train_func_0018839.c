method_start(int local_count, int max_stack, int param_count, const char *name)
{
int n;

  if (strcmp(name, "main") == 0)
  {
    fprintf(out, "}\n\n");
    is_main = true;
  }

  fprintf(out, "int32_t %s(", name);
  for (n = 0; n < param_count; n++)
  {
    if (n != 0) { fprintf(out, ", "); }
    fprintf(out, "int local_%d", n);
  }
  fprintf(out, ")\n");
  fprintf(out, "{\n");

  for (n = 0; n < local_count - param_count; n++)
  {
    fprintf(out, "  xint32_t local_%d;\n", param_count + n);
  }

  for (n = 0; n < max_stack; n++)
  {
    fprintf(out, "  xint32_t stack_%d;\n", n);
  }

  fprintf(out, "\n");

  if (is_main) { fprintf(out, "  init();\n"); }

  stack = 0;
  temp_var = false;
}
