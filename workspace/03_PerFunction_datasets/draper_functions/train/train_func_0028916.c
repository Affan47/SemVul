end_print(GtkPrintOperation *operation, GtkPrintContext *context, gpointer user_data)
{
	DocInfo *dinfo = user_data;

	if (dinfo == NULL)
		return;

	gtk_widget_hide(main_widgets.progressbar);
	g_object_unref(dinfo->sci);
	g_object_unref(dinfo->layout);
	g_array_free(dinfo->pages, TRUE);
}
