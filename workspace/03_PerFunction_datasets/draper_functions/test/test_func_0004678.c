on_notebook_downloads_switch_page(GtkNotebook *notebook,
	GtkNotebookPage *unused_page, int page_num, void *unused_udata)
{
	(void) unused_udata;
	(void) unused_page;

	g_return_if_fail(UNSIGNED(page_num) < nb_downloads_page_num);
	g_return_if_fail(UNSIGNED(current_page) < nb_downloads_page_num);

	fi_gui_files_widget_destroy();

	current_page = page_num;
	notebook_downloads_init_page(notebook, current_page);
}
