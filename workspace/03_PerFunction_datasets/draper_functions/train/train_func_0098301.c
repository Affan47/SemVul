cl_target_option_restore (struct gcc_options *opts, struct cl_target_option *ptr)
{
  opts->x_target_flags = ptr->x_target_flags;

  if (targetm.target_option.restore)
    targetm.target_option.restore (ptr);
}
