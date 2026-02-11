process_create_tab (GeditWindow *window,
                    GtkWidget   *notebook,
                    GeditTab    *tab,
                    gboolean     jump_to)
{
	if (tab == NULL)
	{
		return NULL;
	}

	gedit_debug (DEBUG_WINDOW);

	gtk_widget_show (GTK_WIDGET (tab));
	gedit_notebook_add_tab (GEDIT_NOTEBOOK (notebook),
	                        tab,
	                        -1,
	                        jump_to);

	if (!gtk_widget_get_visible (GTK_WIDGET (window)))
	{
		gtk_window_present (GTK_WINDOW (window));
	}

	return tab;
}
