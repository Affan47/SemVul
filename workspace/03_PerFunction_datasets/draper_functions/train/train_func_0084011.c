_folks_backends_tp_backend_account_enabled_cb (FolksBackendsTpBackend* self, TpAccount* account) {
	TpAccount* _tmp0_ = NULL;
	gboolean _tmp1_ = FALSE;
	gboolean _tmp2_ = FALSE;
	gboolean _tmp3_ = FALSE;
	GeeSet* _tmp4_ = NULL;
	gboolean _tmp9_ = FALSE;
	TpfPersonaStore* store = NULL;
	TpAccount* _tmp10_ = NULL;
	TpfPersonaStore* _tmp11_ = NULL;
	TpfPersonaStore* _tmp12_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (account != NULL);
	_tmp0_ = account;
	g_object_get (_tmp0_, "enabled", &_tmp1_, NULL);
	_tmp2_ = _tmp1_;
	if (!_tmp2_) {
		return;
	}
	_tmp4_ = self->priv->_storeids;
	if (_tmp4_ != NULL) {
		GeeSet* _tmp5_ = NULL;
		TpAccount* _tmp6_ = NULL;
		const gchar* _tmp7_ = NULL;
		gboolean _tmp8_ = FALSE;
		_tmp5_ = self->priv->_storeids;
		_tmp6_ = account;
		_tmp7_ = tp_proxy_get_object_path ((TpProxy*) _tmp6_);
		_tmp8_ = gee_collection_contains ((GeeCollection*) _tmp5_, _tmp7_);
		_tmp3_ = _tmp8_ == FALSE;
	} else {
		_tmp3_ = FALSE;
	}
	_tmp9_ = _tmp3_;
	if (_tmp9_) {
		return;
	}
	_tmp10_ = account;
	_tmp11_ = tpf_persona_store_dup_for_account (_tmp10_);
	store = _tmp11_;
	_tmp12_ = store;
	_folks_backends_tp_backend_add_store (self, (FolksPersonaStore*) _tmp12_, TRUE);
	_g_object_unref0 (store);
}
