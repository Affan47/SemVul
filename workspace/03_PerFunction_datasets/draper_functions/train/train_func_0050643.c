is_valid_uuid (const gchar *str)
{
  gboolean ret = FALSE;
  guint groups[] = {8, 4, 4, 4, 12, 0};
  guint pos, n, m;

  if (strlen (str) != 36)
    goto out;

  pos = 0;
  for (n = 0; groups[n] != 0; n++)
    {
      if (pos > 0)
        {
          if (str[pos++] != '-')
            goto out;
        }
      for (m = 0; m < groups[n]; m++)
        {
          if (!g_ascii_isxdigit (str[pos++]))
            goto out;
        }
    }

  ret = TRUE;

 out:
  return ret;
}
