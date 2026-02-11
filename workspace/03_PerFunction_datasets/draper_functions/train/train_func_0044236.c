cb_sheet_label_drag_leave (GtkWidget *widget, GdkDragContext *context,
			   guint time, WBCGtk *wbcg)
{
	GtkWidget *w_source, *arrow;


	w_source = gtk_drag_get_source_widget (context);
	if (w_source) {
		arrow = g_object_get_data (G_OBJECT (w_source), "arrow");
		gtk_widget_hide (arrow);
	}
}
