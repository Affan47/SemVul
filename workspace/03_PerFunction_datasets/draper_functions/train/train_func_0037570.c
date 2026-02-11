unity_protocol_preview_real_end_updates_as_hashtable (UnityProtocolPreview* self) {
	GHashTable* result = NULL;
	GHashTable* _tmp0_ = NULL;
	GHashTable* _result_ = NULL;
	GHashTable* _tmp1_ = NULL;
	GHashTable* _tmp2_ = NULL;
	_tmp0_ = self->priv->_updates;
	if (_tmp0_ == NULL) {
		g_warning ("protocol-previews.vala:132: Called end_updates without begin_updates");
	}
	_tmp1_ = self->priv->_updates;
	_tmp2_ = _g_hash_table_ref0 (_tmp1_);
	_result_ = _tmp2_;
	_g_hash_table_unref0 (self->priv->_updates);
	self->priv->_updates = NULL;
	result = _result_;
	return result;
}
