cc_wacom_nav_button_update (CcWacomNavButton *nav)
{
	CcWacomNavButtonPrivate *priv = nav->priv;
	int num_pages;
	int current_page;
	char *text;

	if (priv->notebook == NULL) {
		gtk_widget_hide (GTK_WIDGET (nav));
		return;
	}

	num_pages = gtk_notebook_get_n_pages (GTK_NOTEBOOK (priv->notebook));
	if (num_pages == 0)
		return;
	if (priv->ignore_first_page && num_pages == 1)
		return;

	if (priv->ignore_first_page)
		num_pages--;

	g_assert (num_pages >= 1);

	if (num_pages == 1)
		gtk_widget_hide (GTK_WIDGET (nav));
	else
		gtk_widget_show (GTK_WIDGET (nav));

	current_page = gtk_notebook_get_current_page (GTK_NOTEBOOK (priv->notebook));
	if (current_page < 0)
		return;
	if (priv->ignore_first_page)
		current_page--;
	gtk_widget_set_sensitive (priv->prev, current_page == 0 ? FALSE : TRUE);
	gtk_widget_set_sensitive (priv->next, current_page + 1 == num_pages ? FALSE : TRUE);

	text = g_strdup_printf (_("%d of %d"),
				current_page + 1,
				num_pages);
	gtk_label_set_text (GTK_LABEL (priv->label), text);
}
