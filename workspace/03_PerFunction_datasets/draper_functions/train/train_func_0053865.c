entry_answer(GtkWidget *widget, gpointer data)
{
	choice = (int)(long)data;
	if (!choice) {
		strncpy(outmsg, gtk_entry_get_text(GTK_ENTRY(entry)), outmsglen - 1);
	} else
		strcpy(outmsg, "");
	gtk_widget_destroy(dialog);
	dialog = NULL;
}
