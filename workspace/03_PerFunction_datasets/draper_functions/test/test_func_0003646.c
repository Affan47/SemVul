smb_name_to_utf8 (const char *name, gboolean *valid_utf8_out)
{
  GString *string;
  const gchar *remainder, *invalid;
  gint remaining_bytes, valid_bytes;
  gboolean valid_utf8;

  remainder = name;
  remaining_bytes = strlen (name);
  valid_utf8 = TRUE;

  string = g_string_sized_new (remaining_bytes);
  while (remaining_bytes != 0)
    {
      if (g_utf8_validate (remainder, remaining_bytes, &invalid))
	break;
      valid_utf8 = FALSE;

      valid_bytes = invalid - remainder;

      g_string_append_len (string, remainder, valid_bytes);

      g_string_append (string, "\357\277\275");

      remaining_bytes -= valid_bytes + 1;
      remainder = invalid + 1;
    }

  g_string_append (string, remainder);

  if (valid_utf8_out)
    *valid_utf8_out = valid_utf8;

  return g_string_free (string, FALSE);
}
