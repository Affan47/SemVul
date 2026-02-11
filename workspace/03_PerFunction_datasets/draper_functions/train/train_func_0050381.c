summary_drag_motion_cb(GtkWidget      *widget,
					  GdkDragContext *context,
					  gint            x,
					  gint            y,
					  guint           time,
					  SummaryView	 *summaryview)
{
	FolderItem *item = summaryview->folder_item;
	if (!(item && item->folder && folder_item_parent(item) != NULL
		    && FOLDER_CLASS(item->folder)->add_msg != NULL)) {
		gdk_drag_status(context, 0, time);
		return FALSE;
	} else if (gtk_drag_get_source_widget(context) ==
		mainwindow_get_mainwindow()->folderview->ctree) {

		gdk_drag_status(context, 0, time);
		return FALSE;
	} else if (gtk_drag_get_source_widget(context) ==
		summaryview->ctree) {

		gdk_drag_status(context, 0, time);
		return FALSE;
	} else {
		gdk_drag_status(context, GDK_ACTION_COPY, time);
		return TRUE;
	}
}
