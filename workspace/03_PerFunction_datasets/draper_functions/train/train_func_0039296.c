unity_internal_results_synchronizer_clear_provider_model (UnityInternalResultsSynchronizer* self, const gchar* scope_id) {
	DeeModel* provider = NULL;
	GHashTable* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	gconstpointer _tmp2_ = NULL;
	DeeModel* _tmp3_ = NULL;
	DeeModel* _tmp4_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (scope_id != NULL);
	_tmp0_ = self->priv->_provider_ids;
	_tmp1_ = scope_id;
	_tmp2_ = g_hash_table_lookup (_tmp0_, _tmp1_);
	_tmp3_ = _g_object_ref0 ((DeeModel*) _tmp2_);
	provider = _tmp3_;
	_tmp4_ = provider;
	if (_tmp4_ != NULL) {
		UnityInternalResultsSynchronizerSignalHandlers* handlers = NULL;
		GHashTable* _tmp5_ = NULL;
		DeeModel* _tmp6_ = NULL;
		gconstpointer _tmp7_ = NULL;
		gboolean was_blocked = FALSE;
		UnityInternalResultsSynchronizerSignalHandlers* _tmp8_ = NULL;
		gboolean _tmp9_ = FALSE;
		const gchar* _tmp10_ = NULL;
		DeeModel* _tmp11_ = NULL;
		gboolean _tmp12_ = FALSE;
		_tmp5_ = self->priv->_provider_signal_ids;
		_tmp6_ = provider;
		_tmp7_ = g_hash_table_lookup (_tmp5_, _tmp6_);
		handlers = (UnityInternalResultsSynchronizerSignalHandlers*) _tmp7_;
		_tmp8_ = handlers;
		_tmp9_ = (*_tmp8_).blocked;
		was_blocked = _tmp9_;
		_tmp10_ = scope_id;
		unity_internal_results_synchronizer_enable_provider (self, _tmp10_);
		_tmp11_ = provider;
		dee_model_clear (_tmp11_);
		_tmp12_ = was_blocked;
		if (_tmp12_) {
			const gchar* _tmp13_ = NULL;
			_tmp13_ = scope_id;
			unity_internal_results_synchronizer_disable_provider (self, _tmp13_);
		}
	}
	_g_object_unref0 (provider);
}
