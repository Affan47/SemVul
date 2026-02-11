check_1 (int gate, enum ld_plugin_level level, const char *text)
{
  if (gate)
    return;

  if (message)
    message (level, text);
  else
    {

      fprintf (stderr, "%s\n", text);
      if (level == LDPL_FATAL)
	abort ();
    }
}
