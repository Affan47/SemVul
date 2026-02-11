symbol_bd_css_has_cache(gchar *cache_str, gchar *cache_completion, gint cache_flags, const gchar *symbol_prefix, gint flags)
{
  if (cache_flags != flags) return FALSE;
  gint len = strlen(cache_str);
  return (len !=0 && strlen(symbol_prefix) > len && g_str_has_prefix(symbol_prefix, cache_str));
}
