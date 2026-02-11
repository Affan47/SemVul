voy_cookie_print(struct VoyCookie const *cookie) {
  gchar *result;
  gchar *tmp;
  result = g_strconcat(cookie->name, "=", cookie->value, NULL);
  if (cookie->domain != NULL) {
    tmp = result;
    result = g_strconcat(tmp, "; Domain=", cookie->domain, NULL);
    g_free(tmp);
  }
  if (cookie->path != NULL) {
    tmp = result;
    result = g_strconcat(tmp, "; Path=", cookie->path, NULL);
    g_free(tmp);
  }
  if (cookie->expires != NULL) {
    gchar *date_time = g_date_time_format(cookie->expires, VOY_COOKIE_TIME_FORMAT);
    tmp = result;
    result = g_strconcat(tmp, "; Expires=", date_time, NULL);
    g_free(date_time);
    g_free(tmp);
  }
  if (cookie->secure == TRUE) {
    tmp = result;
    result = g_strconcat(tmp, "; Secure", NULL);
    g_free(tmp);
  }
  if (cookie->http_only == TRUE) {
    tmp = result;
    result = g_strconcat(tmp, "; HttpOnly", NULL);
    g_free(tmp);
  }
  return result;
}
