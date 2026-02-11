save_as_ok (GtkWidget *w __unused, GtkFileSelection *fs) {
    size_t length;
    const gchar *filename;
    filename = gtk_file_selection_get_filename (GTK_FILE_SELECTION (fs));
    if (glbl_selected_filename_str != NULL) {
	free(glbl_selected_filename_str);
    }
    if (filename != NULL) {
	length = strlen(filename);
	glbl_selected_filename_str = calloc(length + 1, sizeof(gchar));
	strncpy(glbl_selected_filename_str, filename, length);
	glbl_selected_filename_str[length] = '\0';
    }
    gtk_widget_destroy (GTK_WIDGET (fs));


    g_string_erase(glbl_window_title_gstr, 0, glbl_window_title_gstr->len);


    g_string_assign(glbl_window_title_gstr, "gtkcookie - ");
    g_string_append(glbl_window_title_gstr, glbl_selected_filename_str);

    gtk_window_set_title(GTK_WINDOW (glbl_main_window), glbl_window_title_gstr->str);


    save_file(NULL, NULL);
}
