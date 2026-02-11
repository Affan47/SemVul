generic_dialog_delete_cb(GtkWidget *w, GdkEventAny *event, gpointer data)
{
	GenericDialog *gd = data;
	gboolean auto_close;

	auto_close = gd->auto_close;

	if (gd->cancel_cb) gd->cancel_cb(gd, gd->data);
	if (auto_close) generic_dialog_close(gd);

	return TRUE;
}
