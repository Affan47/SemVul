gen_tmp_name (const char *prefix,
              const char *suffix)
{
  static const char table[] = "ABCEDEFGHIJKLMNOPQRSTUVWXYZabcedefghijklmnopqrstuvwxyz0123456789";
  GString *str = g_string_new ("");
  guint i;

  if (!prefix)
    prefix = get_default_tmp_prefix ();
  if (!suffix)
    suffix = "tmp";

  g_string_append (str, prefix);
  for (i = 0; i < 8; i++)
    {
      int offset = g_random_int_range (0, sizeof (table) - 1);
      g_string_append_c (str, (guint8)table[offset]);
    }
  g_string_append_c (str, '.');
  g_string_append (str, suffix);

  return g_string_free (str, FALSE);
}
