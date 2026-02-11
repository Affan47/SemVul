nautilus_notebook_is_valid_relative_position (NautilusNotebook *notebook,
					      int offset)
{
	GtkNotebook *gnotebook;
	int page;
	int n_pages;

	gnotebook = GTK_NOTEBOOK (notebook);

	page = gtk_notebook_get_current_page (gnotebook);
	n_pages = gtk_notebook_get_n_pages (gnotebook) - 1;
	if (page < 0 ||
	    (offset < 0 && page < -offset) ||
	    (offset > 0 && page > n_pages - offset)) {
		return FALSE;
	}

	return TRUE;
}
