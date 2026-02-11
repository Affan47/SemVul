get_locale (void)
{
  const char *loc = NULL;
  gchar *ret;

#ifdef ENABLE_NLS
#if defined(LC_MESSAGES)
  loc = setlocale (LC_MESSAGES, NULL);
  GST_LOG ("LC_MESSAGES: %s", GST_STR_NULL (loc));
#elif defined(LC_ALL)
  loc = setlocale (LC_ALL, NULL);
  GST_LOG ("LC_ALL: %s", GST_STR_NULL (loc));
#else
  GST_LOG ("Neither LC_ALL nor LC_MESSAGES defined");
#endif
#else
  GST_LOG ("i18n disabled");
#endif

  if (loc == NULL || g_ascii_strncasecmp (loc, "en", 2) == 0)
    return NULL;


  ret = g_ascii_strdown (loc, -1);
  ret = g_strcanon (ret, "abcdefghijklmnopqrstuvwxyz", '\0');
  GST_LOG ("using locale: %s", ret);
  return ret;
}
