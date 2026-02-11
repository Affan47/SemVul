summary_start_drag(GtkWidget *widget, gint button, GdkEvent *event,
			       SummaryView *summaryview)
{
	GdkDragContext *context;

	cm_return_if_fail(summaryview != NULL);
	cm_return_if_fail(summaryview->folder_item != NULL);
	cm_return_if_fail(summaryview->folder_item->folder != NULL);

	if (summaryview->selected == NULL) return;

	context = gtk_drag_begin(widget, summaryview->target_list,
				 GDK_ACTION_MOVE|GDK_ACTION_COPY|GDK_ACTION_DEFAULT, button, event);
	gtk_drag_set_icon_default(context);
	if (prefs_common.layout_mode == SMALL_LAYOUT) {
		GtkWidget *paned = gtk_widget_get_parent(GTK_WIDGET_PTR(summaryview));
		if (paned && GTK_IS_PANED(paned)) {
	        	mainwindow_reset_paned(GTK_PANED(paned));
		}
	}
}
