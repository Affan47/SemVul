gedit_notebook_add_tab (GeditNotebook *nb,
		        GeditTab      *tab,
		        gint           position,
		        gboolean       jump_to)
{
	GtkWidget *tab_label;

	g_return_if_fail (GEDIT_IS_NOTEBOOK (nb));
	g_return_if_fail (GEDIT_IS_TAB (tab));

	tab_label = create_tab_label (nb, tab);

	gtk_notebook_insert_page (GTK_NOTEBOOK (nb),
				  GTK_WIDGET (tab),
				  tab_label,
				  position);
	gtk_notebook_set_tab_reorderable (GTK_NOTEBOOK (nb),
	                                  GTK_WIDGET (tab),
	                                  TRUE);
	gtk_notebook_set_tab_detachable (GTK_NOTEBOOK (nb),
	                                 GTK_WIDGET (tab),
	                                 TRUE);


	position = gtk_notebook_page_num (GTK_NOTEBOOK (nb),
					  GTK_WIDGET (tab));

	if (jump_to)
	{
		gtk_notebook_set_current_page (GTK_NOTEBOOK (nb), position);
		gtk_widget_grab_focus (GTK_WIDGET (tab));
	}
}
