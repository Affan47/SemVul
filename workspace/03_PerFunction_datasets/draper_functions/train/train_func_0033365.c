maybe_default_options (struct gcc_options *opts,
		       struct gcc_options *opts_set,
		       const struct default_options *default_opts,
		       int level, bool size, bool fast, bool debug,
		       unsigned int lang_mask,
		       const struct cl_option_handlers *handlers,
		       location_t loc,
		       diagnostic_context *dc)
{
  size_t i;

  for (i = 0; default_opts[i].levels != OPT_LEVELS_NONE; i++)
    maybe_default_option (opts, opts_set, &default_opts[i],
			  level, size, fast, debug,
			  lang_mask, handlers, loc, dc);
}
