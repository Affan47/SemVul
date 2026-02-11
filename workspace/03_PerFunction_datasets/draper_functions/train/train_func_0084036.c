parse_d (const struct parser_table* entry, char **argv, int *arg_ptr)
{
  if (options.warnings)
    {
      error (0, 0,
	     _("warning: the -d option is deprecated; please use "
	       "-depth instead, because the latter is a "
	       "POSIX-compliant feature."));
    }
  return parse_depth(entry, argv, arg_ptr);
}
