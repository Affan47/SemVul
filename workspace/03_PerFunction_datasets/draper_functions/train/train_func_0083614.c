parse_opt_set_default_format (const char *format)
{
  struct format *frm;

  if (!format)
    format = system_default_format ? system_default_format : "default";

  for (frm = formats; frm->name; frm++)
    if (!strcmp (format, frm->name)) break;
  if (frm == NULL || frm->templ == NULL)
    error (EXIT_FAILURE, 0, "%s: unknown output format", format);
  default_format = frm->templ;
}
