smart_tab_switching_on_closure (GeditNotebook *nb,
				GeditTab      *tab)
{
	if (nb->priv->focused_pages)
	{
		GList *l;
		GtkWidget *child;
		gint page_num;


		l = g_list_last (nb->priv->focused_pages);
		child = GTK_WIDGET (l->data);

		page_num = gtk_notebook_page_num (GTK_NOTEBOOK (nb),
		                                  child);

		gtk_notebook_set_current_page (GTK_NOTEBOOK (nb),
		                               page_num);
	}
}
