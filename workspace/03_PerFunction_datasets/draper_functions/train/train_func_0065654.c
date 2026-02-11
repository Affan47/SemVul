set_output_flag(int flag)
{
  if(param.output_flags <= 0) param.output_flags = flag;
  else param.output_flags |= flag;
}
