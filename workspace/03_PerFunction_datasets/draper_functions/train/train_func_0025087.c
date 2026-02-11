pop_integer_local(int index)
{
  if (stack > 0)
  {
    fprintf(out, "  pop -%d(r12)  ; pop local_%d\n", LOCALS(index), index);
    stack--;
  }
    else
  if (reg > 0)
  {
    fprintf(out, "  mov.w r%d, -%d(r12) ; pop local_%d\n", REG_STACK(reg-1), LOCALS(index), index);
    reg--;
  }
    else
  {
    printf("Internal Error: Nothing on the stack?\n");
    return -1;
  }

  return 0;
}
