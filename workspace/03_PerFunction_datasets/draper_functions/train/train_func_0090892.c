invoke_static_method(const char *name, int params, int is_void)
{
int local;
int stack_vars = stack;

  printf("invoke_static_method() name=%s params=%d is_void=%d\n", name, params, is_void);

  fprintf(out, "; invoke_static_method\n");

  local = -params;
  while(local != 0)
  {
    if (stack_vars > 0)
    {
      fprintf(out, "  ldi YL, stack_lo + 1 + %d\n", (stack - stack_vars));
      fprintf(out, "  add YL, SP\n");
      fprintf(out, "  ld temp, Y\n");
      fprintf(out, "  ldi YL, stack_lo + 1 %d\n", local - 1);
      fprintf(out, "  add YL, SP\n");
      fprintf(out, "  st Y, temp\n");
      fprintf(out, "  ldi YL, stack_hi + 1 + %d\n", (stack - stack_vars));
      fprintf(out, "  add YL, SP\n");
      fprintf(out, "  ld temp, Y\n");
      fprintf(out, "  ldi YL, stack_hi + 1 %d\n", local - 1);
      fprintf(out, "  add YL, SP\n");
      fprintf(out, "  st Y, temp\n");

      stack_vars--;
    }

    local++;
  }

  CALL(name);

  if ((stack - stack_vars) > 0)
  {
    fprintf(out, "  ldi temp, %d\n", (stack - stack_vars));
    fprintf(out, "  add SP, temp\n");

    params -= (stack - stack_vars);
  }

  if (!is_void)
  {
    PUSH_LO("result0");
    PUSH_HI("result1");
    stack++;
  }

  return 0;
}
