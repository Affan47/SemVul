record_eos_msg_cb (GstBus * bus, GstMessage * msg, GSRWindow * window)
{
	g_return_if_fail (GSR_IS_WINDOW (window));

	GST_DEBUG ("EOS. Finished recording");


	set_pipeline_state_to_null (window->priv->record->pipeline);

	g_free (window->priv->working_file);
	window->priv->working_file = g_strdup (window->priv->record_filename);

	g_free (window->priv->filename);
	window->priv->filename = g_strdup (window->priv->record_filename);

	window->priv->has_file = TRUE;
}
