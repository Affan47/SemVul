unity_protocol_preview_real_add_properties (UnityProtocolPreview* self, GHashTable* properties) {
	gboolean _tmp0_ = FALSE;
	g_return_if_fail (properties != NULL);
	_tmp0_ = self->priv->_no_details;
	if (_tmp0_) {
		GHashTable* _tmp1_ = NULL;
		gchar* _tmp2_ = NULL;
		GVariant* _tmp3_ = NULL;
		_tmp1_ = properties;
		_tmp2_ = g_strdup ("no-details");
		_tmp3_ = g_variant_new_boolean (TRUE);
		g_variant_ref_sink (_tmp3_);
		g_hash_table_insert (_tmp1_, _tmp2_, _tmp3_);
	}
}
