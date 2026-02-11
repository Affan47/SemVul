_tpl_debug_set_flags_from_env (void)
{
  guint nkeys;
  const gchar *flags_string;

  for (nkeys = 0; keys[nkeys].value; nkeys++);

  flags_string = g_getenv ("TPL_DEBUG");

  if (flags_string != NULL)
    _tpl_debug_set_flags (g_parse_debug_string (flags_string, keys, nkeys));

  tp_debug_set_flags (g_getenv ("TP_DEBUG"));
}
