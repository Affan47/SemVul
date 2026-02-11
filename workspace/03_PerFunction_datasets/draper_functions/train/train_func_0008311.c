pan_search_status(PanWindow *pw, const gchar *text)
{
	gtk_label_set_text(GTK_LABEL(pw->search_label), (text) ? text : "");
}
