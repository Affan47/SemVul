file_already_open_warning_info_bar_response (GtkWidget   *info_bar,
					     gint         response_id,
					     GeditTab    *tab)
{
	GeditView *view;

	view = gedit_tab_get_view (tab);

	if (response_id == GTK_RESPONSE_YES)
	{
		tab->priv->not_editable = FALSE;

		gtk_text_view_set_editable (GTK_TEXT_VIEW (view),
					    TRUE);
	}

	gtk_widget_destroy (info_bar);

	gtk_widget_grab_focus (GTK_WIDGET (view));
}
