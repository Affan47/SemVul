goa_utils_parse_email_address (const gchar *email, gchar **out_username, gchar **out_domain)
{
  gchar *at;
  gchar *dot;

  if (email == NULL || email[0] == '\0')
    return FALSE;

  at = strchr (email, '@');
  if (at == NULL || *(at + 1) == '\0')
    return FALSE;

  dot = strchr (at + 1, '.');
  if (dot == NULL || *(dot + 1) == '\0')
    return FALSE;

  if (out_username != NULL)
    {
      *out_username = g_strdup (email);
      (*out_username)[at - email] = '\0';
    }

  if (out_domain != NULL)
    *out_domain = g_strdup (at + 1);

  return TRUE;
}
