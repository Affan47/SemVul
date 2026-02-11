get_fixed_custom_param(gchar *param)
{
  gchar *parameters = NULL;

  gchar *par = param;
  if (g_str_has_suffix(param, ")")) {
    gint len = strlen(param) - 1;
    if (len != 0) {
      parameters = g_malloc0(len);
      strncpy(parameters, param, len);
      par = parameters;
    } else {
      par = NULL;
    }
  } else {
    par = g_strdup(param);
  }
  return par;
}
