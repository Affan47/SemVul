handle_deferred_opts (void)
{
  size_t i;
  struct deps *deps;


  if (!deps_seen)
    return;

  deps = cpp_get_deps (parse_in);

  for (i = 0; i < deferred_count; i++)
    {
      struct deferred_opt *opt = &deferred_opts[i];

      if (opt->code == OPT_MT || opt->code == OPT_MQ)
	deps_add_target (deps, opt->arg, opt->code == OPT_MQ);
    }
}
