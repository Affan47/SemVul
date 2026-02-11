gitg_repository_dialog_close (void)
{
	if (repository_dialog)
	{
		gtk_widget_destroy (GTK_WIDGET (repository_dialog));
	}
}
