mop_cond_branch(BOOL cond)
{
  zbyte branch = HIBYTE(PC);
  PC++;
  if((branch >> 7) ^ cond)
    skip_branch(branch);
  else
    take_branch(branch);
}
