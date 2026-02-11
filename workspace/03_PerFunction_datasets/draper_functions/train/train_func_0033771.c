go_data_emit_changed (GOData *dat)
{
	GODataClass const *klass = GO_DATA_GET_CLASS (dat);

	g_return_if_fail (klass != NULL);

	if (klass->emit_changed)
		(*klass->emit_changed) (dat);

	g_signal_emit (G_OBJECT (dat), go_data_signals [CHANGED], 0);
}
