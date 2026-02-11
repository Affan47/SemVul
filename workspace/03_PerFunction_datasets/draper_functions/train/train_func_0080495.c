unity_internal_results_synchronizer_finalize (GObject* obj) {
	UnityInternalResultsSynchronizer * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, UNITY_INTERNAL_TYPE_RESULTS_SYNCHRONIZER, UnityInternalResultsSynchronizer);
	_g_free0 (self->priv->_owner_scope_id);
	_g_object_unref0 (self->priv->_merge_strategy);
	_g_hash_table_unref0 (self->priv->_providers);
	_g_hash_table_unref0 (self->priv->_provider_ids);
	_g_hash_table_unref0 (self->priv->_provider_signal_ids);
	_g_hash_table_unref0 (self->priv->_provider_tags);
	_g_hash_table_unref0 (self->priv->_clear_seqnum_tags);
	self->priv->row_buf = (_vala_array_free (self->priv->row_buf, self->priv->row_buf_length1, (GDestroyNotify) g_variant_unref), NULL);
	G_OBJECT_CLASS (unity_internal_results_synchronizer_parent_class)->finalize (obj);
}
