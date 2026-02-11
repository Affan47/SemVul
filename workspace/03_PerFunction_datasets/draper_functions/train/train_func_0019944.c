_gda_data_model_signal_emit_changed (GdaDataModel *model)
{
	g_return_if_fail (GDA_IS_DATA_MODEL (model));

	if (do_notify_changes (model))
		g_signal_emit (model, gda_data_model_signals[CHANGED], 0);
}
