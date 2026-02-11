SaveDTMF()
{
	FILE *f;
	gchar buf[80];

	if ((f = fopen(saveFileName, "w")) == NULL) {
		g_snprintf(buf, 80, _("Can't open file %s for writing!\n"), saveFileName);
		gtk_label_set_text(GTK_LABEL(errorDialog.text), buf);
		gtk_widget_show(errorDialog.dialog);
		return;
	}

	fputs(gtk_entry_get_text(GTK_ENTRY(displayEntry)), f);
	fclose(f);
}
