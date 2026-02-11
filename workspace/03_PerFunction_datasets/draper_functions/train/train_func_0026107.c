cl_target_option_save (struct cl_target_option *ptr, struct gcc_options *opts)
{
  if (targetm.target_option.save)
    targetm.target_option.save (ptr);

  ptr->x_target_flags = opts->x_target_flags;
  ptr->x_ix86_isa_flags = opts->x_ix86_isa_flags;
}
