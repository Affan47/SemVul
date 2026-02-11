set_name_cmp_mode(DACS_name_cmp cmp_mode)
{
  DACS_name_cmp prev_mode;

  prev_mode = name_cmp_mode_default;
  name_cmp_mode_default = cmp_mode;

  log_msg((LOG_TRACE_LEVEL, "Set name_cmp_mode_default to %d", cmp_mode));
  return(prev_mode);
}
