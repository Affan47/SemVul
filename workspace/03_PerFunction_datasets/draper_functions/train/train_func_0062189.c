save_file(GtkWidget *parent, char *filename)
{
	FILE *file;
	char *text;
	GtkTextIter start, end;

	file = fopen(filename,"w");

	if (!file) {
		char *txt = g_strdup_printf("\nCould not save the file\n%s !\n",filename);
		infobox(parent, txt);
		g_free(txt);
		return;
	}
	else {
		gtk_text_buffer_get_bounds(etextbuffer, &start, &end);
		text = gtk_text_buffer_get_text(etextbuffer, &start, &end, TRUE);

		if (g_utf8_validate(text, -1, NULL))
			text = g_locale_from_utf8(text, -1, NULL, NULL, NULL);

		fprintf(file,text);
		fclose(file);
		efname = filename;
		buffer_saved();
		if (GTK_IS_FILE_CHOOSER(parent)) gtk_widget_destroy(parent);
	}
	chdir(g_dirname(filename));
}
