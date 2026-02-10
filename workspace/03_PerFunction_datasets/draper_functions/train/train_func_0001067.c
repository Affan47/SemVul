parse_params_obsolete_callback(CS& cmd)
{
  return ONE_OF
    || Get(cmd, "l",	&_length)
    || Get(cmd, "w",	&_width)
    || EVAL_BM_ACTION_BASE::parse_params_obsolete_callback(cmd)
    ;
}
