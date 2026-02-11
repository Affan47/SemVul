g_strdel (gchar * str, gchar rc)
{
  int i = 0, j = 0, len, num = 0;
  len = strlen (str);
  while (i < len) {
    if (str[i] == rc) {
      for (j = i; j < len; j++)
        str[j] = str[j + 1];
      len--;
      num++;
    } else {
      i++;
    }
  }
  return num;
}
