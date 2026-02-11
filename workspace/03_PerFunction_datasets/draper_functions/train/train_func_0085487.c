shell_quote_copy (char *p, const char *string)
{
  if (sh_quoting_options == NULL)
    init_sh_quoting_options ();
  return p + quotearg_buffer (p, (size_t)(-1), string, strlen (string),
                              sh_quoting_options);
}
