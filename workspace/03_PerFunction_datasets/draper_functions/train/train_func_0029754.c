pop_integer_local(int index)
{
  if (reg < REG_MAX)
  {
    fprintf(out, "  mov [ebp-%d], %s\n", LOCALS(index), REG_STACK(--reg));
  }
    else
  {
    fprintf(out, "  pop ebx\n");
    fprintf(out, "  mov [ebp-%d], ebx\n", LOCALS(index));
    stack--;
  }

  return 0;
}
