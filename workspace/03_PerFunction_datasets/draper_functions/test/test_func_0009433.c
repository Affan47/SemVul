sidebar_focus_symbols_tab(void)
{
	if (ui_prefs.sidebar_visible && interface_prefs.sidebar_symbol_visible)
	{
		GtkNotebook *notebook = GTK_NOTEBOOK(main_widgets.sidebar_notebook);
		GtkWidget *symbol_list_scrollwin = gtk_notebook_get_nth_page(notebook, TREEVIEW_SYMBOL);

		gtk_notebook_set_current_page(notebook, TREEVIEW_SYMBOL);
		gtk_widget_grab_focus(gtk_bin_get_child(GTK_BIN(symbol_list_scrollwin)));
	}
}
