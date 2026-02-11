completion_window_apply_selection(GtkTreeView *list_view,
						GtkEntry *entry,
						gboolean move_focus)
{
	gchar *address = NULL, *text = NULL;
	gint   cursor_pos;
	GtkWidget *parent;
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;
	gboolean is_group = FALSE;
	cm_return_if_fail(list_view != NULL);
	cm_return_if_fail(entry != NULL);
	GList *grp_emails = NULL;

	selection = gtk_tree_view_get_selection(list_view);
	if (! gtk_tree_selection_get_selected(selection, &model, &iter))
		return;


	if( _completionIdleID_ != 0 ) {
		g_source_remove( _completionIdleID_ );
		_completionIdleID_ = 0;
	}


	gtk_tree_model_get(model, &iter, ADDR_COMPL_ADDRESS, &text,
				ADDR_COMPL_ISGROUP, &is_group,
				ADDR_COMPL_GROUPLIST, &grp_emails,
				-1);

	address = get_address_from_edit(entry, &cursor_pos);
	g_free(address);
	replace_address_in_edit(entry, text, cursor_pos, is_group, grp_emails);
	g_free(text);


	parent = gtk_widget_get_parent(GTK_WIDGET(entry));
	if( parent && move_focus) {
		gtk_widget_child_focus( parent, GTK_DIR_TAB_FORWARD );
	}
}
