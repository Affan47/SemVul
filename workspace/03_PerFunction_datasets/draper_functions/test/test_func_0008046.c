on_end_loading (GeditFileBrowserStore  *model,
		GtkTreeIter            *iter,
		GeditFileBrowserWidget *obj)
{
	if (!GDK_IS_WINDOW (gtk_widget_get_window (GTK_WIDGET (obj->priv->treeview))))
		return;

	gdk_window_set_cursor (gtk_widget_get_window (GTK_WIDGET (obj)), NULL);
}
