change_callback(GtkWidget *entry, gpointer func_data) {
    const gchar *entry_text;
    int i;
    size_t field_length;

    i = *(int *) func_data;
    entry_text = gtk_entry_get_text(GTK_ENTRY(entry));

    if (entry_text != NULL) {
	field_length = strlen(entry_text);

	if (glbl_selected_cookie[i] != NULL) {
	    free(glbl_selected_cookie[i]);
	}
	glbl_selected_cookie[i] = calloc(field_length + 1, sizeof(gchar));
	strncpy(glbl_selected_cookie[i], entry_text, field_length);
	glbl_selected_cookie[i][field_length] = '\0';
    }
}
