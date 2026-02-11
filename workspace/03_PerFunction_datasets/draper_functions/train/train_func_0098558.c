g_string_append_encoded (GString *string,
			 const char *encoded,
			 const char *encoded_end,
			 const char *reserved_chars_allowed)
{
  char c;
  static const gchar hex[16] = "0123456789ABCDEF";

  if (encoded_end == NULL)
    encoded_end = encoded + strlen (encoded);

  while (encoded < encoded_end)
    {
      c = *encoded++;

      if (is_valid (c, reserved_chars_allowed))
	g_string_append_c (string, c);
      else
	{
	  g_string_append_c (string, '%');
	  g_string_append_c (string, hex[((guchar)c) >> 4]);
	  g_string_append_c (string, hex[((guchar)c) & 0xf]);
	}
    }
}
