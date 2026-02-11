check_str(gchar * str1, gchar * str2) {

  if ((str1 == NULL) && (str2 == NULL))
    return TRUE;
  if ((str1 == NULL) || (str2 == NULL))
    return FALSE;
  if (strcmp(str1, str2) == 0)
    return TRUE;

  return FALSE;
}
