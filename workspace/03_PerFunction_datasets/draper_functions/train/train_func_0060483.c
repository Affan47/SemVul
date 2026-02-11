notebook_page_removed (GtkNotebook        *notebook,
		       GtkWidget          *child,
		       guint               page_num,
		       GeditMultiNotebook *mnb)
{
	GeditTab *tab = GEDIT_TAB (child);
	guint num_tabs;
	gboolean last_notebook;

	--mnb->priv->total_tabs;
	num_tabs = gtk_notebook_get_n_pages (notebook);
	last_notebook = (mnb->priv->notebooks->next == NULL);

	if (mnb->priv->total_tabs == 0)
	{
		mnb->priv->active_tab = NULL;

		g_object_notify (G_OBJECT (mnb), "active-tab");
	}

	g_signal_emit (G_OBJECT (mnb), signals[TAB_REMOVED], 0, notebook, tab);


	if (num_tabs == 0 && !mnb->priv->removing_notebook &&
	    !last_notebook)
	{
		remove_notebook (mnb, GTK_WIDGET (notebook));
	}
}
