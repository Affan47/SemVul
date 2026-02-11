collect_save_options (va_list   opts,
                      gchar  ***keys,
                      gchar  ***vals)
{
  gchar *key;
  gchar *val;
  gchar *next;
  gint count;

  count = 0;
  *keys = NULL;
  *vals = NULL;

  next = va_arg (opts, gchar*);
  while (next)
    {
      key = next;
      val = va_arg (opts, gchar*);

      ++count;


      *keys = g_realloc (*keys, sizeof(gchar*) * (count + 1));
      *vals = g_realloc (*vals, sizeof(gchar*) * (count + 1));

      (*keys)[count-1] = g_strdup (key);
      (*vals)[count-1] = g_strdup (val);

      (*keys)[count] = NULL;
      (*vals)[count] = NULL;

      next = va_arg (opts, gchar*);
    }
}
