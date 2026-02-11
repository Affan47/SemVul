unity_protocol_annotated_icon_get_hint (UnityProtocolAnnotatedIcon* self, const gchar* name) {
	GVariant* result = NULL;
	GHashTable* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	gconstpointer _tmp2_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (name != NULL, NULL);
	_tmp0_ = self->priv->_hints;
	_tmp1_ = name;
	_tmp2_ = g_hash_table_lookup (_tmp0_, _tmp1_);
	result = (GVariant*) _tmp2_;
	return result;
}
