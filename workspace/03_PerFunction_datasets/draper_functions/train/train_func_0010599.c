nautilus_notebook_add_tab (NautilusNotebook *notebook,
			   NautilusWindowSlot *slot,
			   int position,
			   gboolean jump_to)
{
	GtkNotebook *gnotebook = GTK_NOTEBOOK (notebook);
	GtkWidget *tab_label;

	g_return_val_if_fail (NAUTILUS_IS_NOTEBOOK (notebook), -1);
	g_return_val_if_fail (NAUTILUS_IS_WINDOW_SLOT (slot), -1);

	tab_label = build_tab_label (notebook, slot);

	position = gtk_notebook_insert_page (GTK_NOTEBOOK (notebook),
					     GTK_WIDGET (slot),
					     tab_label,
					     position);

	gtk_container_child_set (GTK_CONTAINER (notebook),
				 GTK_WIDGET (slot),
				 "tab-expand", TRUE,
				 NULL);

	nautilus_notebook_sync_tab_label (notebook, slot);
	nautilus_notebook_sync_loading (notebook, slot);

	if (jump_to) {
		gtk_notebook_set_current_page (gnotebook, position);
	}

	return position;
}
