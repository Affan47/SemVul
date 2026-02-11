asm_source_create_listing_buffer (AsmSource * self, const gchar * text)
{
  gchar **lines;
  gint cnt = 0;

  g_assert (text);

  lines = g_strsplit (text, "\n", -1);
  g_assert (lines);


  while (lines[cnt])
	{

	  self->listing_buffer[cnt] = g_string_new (lines[cnt]);
	  self->listing_buffer_total = cnt + 1;

	  cnt++;
	}

  g_strfreev (lines);
}
