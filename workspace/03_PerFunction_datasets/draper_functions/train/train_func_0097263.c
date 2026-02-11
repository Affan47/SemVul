gtk_source_completion_hide (GtkSourceCompletion *completion)
{
	g_return_if_fail (GTK_SOURCE_IS_COMPLETION (completion));

	reset_completion (completion);

	if (gtk_widget_get_visible (GTK_WIDGET (completion->priv->main_window)))
	{
		g_signal_emit (completion, signals[HIDE], 0);
	}
}
