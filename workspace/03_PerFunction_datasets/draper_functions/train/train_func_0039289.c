gedit_multi_notebook_set_current_page (GeditMultiNotebook *mnb,
				       gint                page_num)
{
	GList *l;
	gint pages = 0;
	gint single_num = page_num;

	g_return_if_fail (GEDIT_IS_MULTI_NOTEBOOK (mnb));

	for (l = mnb->priv->notebooks; l != NULL; l = g_list_next (l))
	{
		gint p;

		p = gtk_notebook_get_n_pages (GTK_NOTEBOOK (l->data));
		pages += p;

		if ((pages - 1) >= page_num)
			break;

		single_num -= p;
	}

	if (l == NULL)
		return;

	if (GTK_WIDGET (l->data) != mnb->priv->active_notebook)
	{
		gtk_widget_grab_focus (GTK_WIDGET (l->data));
	}

	gtk_notebook_set_current_page (GTK_NOTEBOOK (l->data), single_num);
}
