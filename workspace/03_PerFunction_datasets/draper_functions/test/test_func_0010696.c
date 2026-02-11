write_quoted_string (GIOChannel *channel, GString *string, GError **error)
{
  guint i;

  WRITE_OR_LOSE ("\"");
  for (i = 0; i < string->len; i++)
    {
      if (string->str[i] != '\0')
	{
	  if (!g_io_channel_write_chars (channel, string->str + i, 1, NULL, error))
	    return FALSE;
	}
      else
	{
	  if (!g_io_channel_write_chars (channel, "\\0", -1, NULL, error))
	    return FALSE;
	}
    }
  WRITE_OR_LOSE ("\\0\"");
  return TRUE;
 io_lose:
  return FALSE;
}
