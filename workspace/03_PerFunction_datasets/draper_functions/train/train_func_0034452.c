cb_preview_btn_close(GtkButton *button, gpointer data)
{
	PreviewData *preview_data = (PreviewData *)data;
	if (preview_data->rendering)
		return;
	gtk_widget_destroy(preview_data->dialog);
}
