vte_exited_cb (GtkWidget *widget, gboolean force)
{
	GSQL_TRACE_FUNC;
	if (force)
		GSQL_DEBUG ("Forced closing");
	else
		GSQL_DEBUG ("Regular closing");

	gtk_widget_destroy (GTK_WIDGET (widget));

	return;
}
