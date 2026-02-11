egg_assertion_message_cmpmem (const char     *domain,
                              const char     *file,
                              int             line,
                              const char     *func,
                              const char     *expr,
                              gconstpointer   arg1,
                              gsize           n_arg1,
                              const char     *cmp,
                              gconstpointer   arg2,
                              gsize           n_arg2)
{
  char *a1, *a2, *s;
  a1 = arg1 ? egg_test_escape_data (arg1, n_arg1) : g_strdup ("NULL");
  a2 = arg2 ? egg_test_escape_data (arg2, n_arg2) : g_strdup ("NULL");
  s = g_strdup_printf ("assertion failed (%s): (%s %s %s)", expr, a1, cmp, a2);
  g_free (a1);
  g_free (a2);
  g_assertion_message (domain, file, line, func, s);
  g_free (s);
}
