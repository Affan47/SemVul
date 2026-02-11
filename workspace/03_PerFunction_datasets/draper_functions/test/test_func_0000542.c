async_process_onCancel (AsyncProcess* self) {
	GPid _tmp0_ = 0;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->pid;
	if (((pid_t) _tmp0_) == ((pid_t) 0)) {
		return;
	}
	async_process_onCancelAsync (self, NULL, NULL);
}
