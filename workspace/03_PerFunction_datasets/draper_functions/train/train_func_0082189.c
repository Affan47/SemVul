op_check_arg_count(void)
{
  if(stack_frames[frame_count].arguments >= operand[0])
    mop_take_branch();
  else
    mop_skip_branch();
}
