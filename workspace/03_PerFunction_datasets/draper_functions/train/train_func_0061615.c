usage_long_opt (const struct argp_option *opt,
		const struct argp_option *real,
		const char *domain, void *cookie)
{
  argp_fmtstream_t stream = cookie;
  const char *arg = opt->arg;
  int flags = opt->flags | real->flags;

  if (! arg)
    arg = real->arg;

  if (! (flags & OPTION_NO_USAGE) && !odoc (opt))
    {
      if (arg)
	{
	  arg = dgettext (domain, arg);
	  if (flags & OPTION_ARG_OPTIONAL)
	    __argp_fmtstream_printf (stream, " [--%s[=%s]]", opt->name, arg);
	  else
	    __argp_fmtstream_printf (stream, " [--%s=%s]", opt->name, arg);
	}
      else
	__argp_fmtstream_printf (stream, " [--%s]", opt->name);
    }

  return 0;
}
