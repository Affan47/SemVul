on_insert_text(GtkEditable *editable, gchar *new_text, gint new_text_length,
	G_GNUC_UNUSED gint *position, gpointer gdata)
{
	gboolean valid = TRUE;

	if (new_text_length == -1)
		new_text_length = (gint) strlen(new_text);

	if (GPOINTER_TO_INT(gdata) == VALIDATOR_VARFRAME)
	{
		gchar *s = gtk_editable_get_chars(editable, 0, 1);

		if (*s == '\0' && new_text_length == 1 && (*new_text == '*' || *new_text == '@'))
			new_text_length = 0;
		else if (*s == '*' || *s == '@')
			valid = !new_text_length;

		g_free(s);
	}

	while (new_text_length-- > 0 && valid)
	{
		switch (GPOINTER_TO_INT(gdata))
		{
			case VALIDATOR_NUMERIC : valid = isdigit(*new_text); break;
			case VALIDATOR_NOSPACE : valid = !isspace(*new_text); break;
			case VALIDATOR_VARFRAME :
			{
				valid = isxdigit(*new_text) || tolower(*new_text) == 'x';
				break;
			}
			default : valid = FALSE;
		}
		new_text++;
	}

	if (!valid)
		g_signal_stop_emission_by_name(editable, "insert-text");
}
