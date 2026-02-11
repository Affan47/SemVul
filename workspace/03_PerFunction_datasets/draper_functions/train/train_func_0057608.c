check_whether_orport_reachable(void)
{
  const or_options_t *options = get_options();
  return options->AssumeReachable ||
         can_reach_or_port;
}
