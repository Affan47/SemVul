parser_endif (args)
     char *args;
{
  if (if_stack_depth)
    _rl_parsing_conditionalized_out = if_stack[--if_stack_depth];
  else
    _rl_init_file_error ("$endif without matching $if");
  return 0;
}
