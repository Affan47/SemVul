folderview_start_drag(GtkWidget *widget, gint button, GdkEvent *event,
			          FolderView       *folderview)
{
	GdkDragContext *context;

	cm_return_if_fail(folderview != NULL);
	if (folderview->selected == NULL) return;
	if (folderview->nodes_to_recollapse)
		g_slist_free(folderview->nodes_to_recollapse);
	folderview->nodes_to_recollapse = NULL;
	context = gtk_drag_begin(widget, folderview->target_list,
				 GDK_ACTION_MOVE|GDK_ACTION_COPY|GDK_ACTION_DEFAULT, button, event);
	gtk_drag_set_icon_default(context);
}
