parse_format_string (char const *fmt)
{
  size_t i;
  size_t prefix_len = 0;
  size_t suffix_pos;
  long int pad = 0;
  char *endptr = NULL;

  for (i = 0; !(fmt[i] == '%' && fmt[i + 1] != '%'); i += (fmt[i] == '%') + 1)
    {
      if (!fmt[i])
        error (EXIT_FAILURE, 0,
               _("format %s has no %% directive"), quote (fmt));
      prefix_len++;
    }

  i++;
  i += strspn (fmt + i, " ");
  if (fmt[i] == '\'')
    {
      grouping = 1;
      i++;
    }
  i += strspn (fmt + i, " ");
  errno = 0;
  pad = strtol (fmt + i, &endptr, 10);
  if (errno == ERANGE)
    error (EXIT_FAILURE, 0,
           _("invalid format %s (width overflow)"), quote (fmt));

  if (endptr != (fmt + i) && pad != 0)
    {
      if (pad < 0)
        {
          padding_alignment = MBS_ALIGN_LEFT;
          padding_width = -pad;
        }
      else
        {
          padding_width = pad;
        }
    }
  i = endptr - fmt;

  if (fmt[i] == '\0')
    error (EXIT_FAILURE, 0, _("format %s ends in %%"), quote (fmt));

  if (fmt[i] != 'f')
    error (EXIT_FAILURE, 0, _("invalid format %s,"
                              " directive must be %%['][-][N]f"),
           quote (fmt));
  i++;
  suffix_pos = i;

  for (; fmt[i] != '\0'; i += (fmt[i] == '%') + 1)
    if (fmt[i] == '%' && fmt[i + 1] != '%')
      error (EXIT_FAILURE, 0, _("format %s has too many %% directives"),
             quote (fmt));

  if (prefix_len)
    {
      format_str_prefix = xstrndup (fmt, prefix_len);
      if (!format_str_prefix)
        error (EXIT_FAILURE, 0, _("out of memory (requested %zu bytes)"),
               prefix_len + 1);
    }
  if (fmt[suffix_pos] != '\0')
    {
      format_str_suffix = strdup (fmt + suffix_pos);
      if (!format_str_suffix)
        error (EXIT_FAILURE, 0, _("out of memory (requested %zu bytes)"),
               strlen (fmt + suffix_pos));
    }

  devmsg ("format String:\n  input: %s\n  grouping: %s\n"
                   "  padding width: %ld\n  alignment: %s\n"
                   "  prefix: '%s'\n  suffix: '%s'\n",
          quote (fmt), (grouping) ? "yes" : "no",
          padding_width,
          (padding_alignment == MBS_ALIGN_LEFT) ? "Left" : "Right",
          format_str_prefix, format_str_suffix);
}
