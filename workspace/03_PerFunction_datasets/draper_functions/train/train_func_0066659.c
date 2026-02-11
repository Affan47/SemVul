combo_answer(GtkWidget *widget, gpointer data)
{
	GtkCombo *combo2 = GTK_COMBO(combo);
	choice = (int)(long)data;
	if (!choice) {
		char *extra;
		strncpy(outmsg, gtk_entry_get_text(GTK_ENTRY(combo2->entry)), outmsglen - 1);
		if ((extra = strstr(outmsg, " (")))
			extra[0] = '\0';
	} else
		strcpy(outmsg, "");
	gtk_widget_destroy(dialog);
	dialog = NULL;
}
