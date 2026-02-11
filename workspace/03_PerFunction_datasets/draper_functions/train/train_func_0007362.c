on_page_count_changed(
	GtkNotebook *nb,
	GtkWidget *child,
	guint page_num,
	gpointer user_data
)
{
	if (1 < gtk_notebook_get_n_pages(nb)) {
		gtk_notebook_set_show_tabs(nb, TRUE);
	} else {
		gtk_notebook_set_show_tabs(nb, FALSE);
	}
}
