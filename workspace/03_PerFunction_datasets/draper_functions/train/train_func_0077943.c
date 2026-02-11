dif_parse_header (DifInputContext *ctxt)
{
	while (1) {
		gchar *topic, *num_line, *str_line;
		size_t str_line_len;

		if (!dif_get_line (ctxt))
			return FALSE;
		topic = g_alloca (strlen (ctxt->line) + 1);
		strcpy (topic, ctxt->line);

		if (!dif_get_line (ctxt))
			return FALSE;
		num_line = g_alloca (strlen (ctxt->line) + 1);
		strcpy (num_line, ctxt->line);

		if (!dif_get_line (ctxt))
			return FALSE;
		str_line_len = strlen (ctxt->line);
		str_line = g_alloca (str_line_len + 1);
		strcpy (str_line, ctxt->line);

		if (strcmp (topic, "TABLE") == 0) {
			gchar *name;

			if (str_line_len > 2 && str_line[0] == '"' && str_line[str_line_len - 1] == '"') {
				str_line[str_line_len - 1] = '\0';
				name = str_line + 1;
			}  else {
				name = str_line;
			}
			if (name[0] != '\0') {

			}
		} else if (strcmp (topic, "DATA") == 0) {
			break;
		}


	}

	return TRUE;
}
