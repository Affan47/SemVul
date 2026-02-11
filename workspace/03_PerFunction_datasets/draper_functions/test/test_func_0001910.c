_gtk_error_dialog_from_gerror_run (GtkWindow   *parent,
				   const char  *title,
				   GError      *gerror)
{
	GtkWidget *d;

	g_return_if_fail (gerror != NULL);

	d = _gtk_message_dialog_new (parent,
				     GTK_DIALOG_DESTROY_WITH_PARENT,
				     GTK_STOCK_DIALOG_ERROR,
				     title,
				     gerror->message,
				     GTK_STOCK_OK, GTK_RESPONSE_OK,
				     NULL);
	gtk_dialog_run (GTK_DIALOG (d));

	gtk_widget_destroy (d);
}
