evt_cell_renderer_entry_insert_text(GtkEditable *editable, gchar *new_text, gint new_text_length, gint *position, gpointer user)
{
	LDlgInfo	*ldi = user;
	gchar		*get = new_text, *put = get;


	while(*get)
	{
		if(*get == ldi->separator)
			get++;
		else
			*put++ = *get++;
	}
	*put = '\0';
}
