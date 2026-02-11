unity_category_get_hints (UnityCategory* self) {
	GHashTable* result = NULL;
	GHashTable* _tmp0_ = NULL;
	GHashTable* _tmp4_ = NULL;
	gchar* _tmp5_ = NULL;
	UnityCategoryContentType _tmp6_ = 0;
	const gchar* _tmp7_ = NULL;
	GVariant* _tmp8_ = NULL;
	const gchar* _tmp9_ = NULL;
	GHashTable* _tmp14_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->hints;
	if (_tmp0_ == NULL) {
		GHashFunc _tmp1_ = NULL;
		GEqualFunc _tmp2_ = NULL;
		GHashTable* _tmp3_ = NULL;
		_tmp1_ = g_str_hash;
		_tmp2_ = g_str_equal;
		_tmp3_ = g_hash_table_new_full (_tmp1_, _tmp2_, _g_free0_, _g_variant_unref0_);
		_g_hash_table_unref0 (self->priv->hints);
		self->priv->hints = _tmp3_;
	}
	_tmp4_ = self->priv->hints;
	_tmp5_ = g_strdup ("content-type");
	_tmp6_ = self->priv->_content_type;
	_tmp7_ = unity_category_content_type_to_string (_tmp6_);
	_tmp8_ = g_variant_new_string (_tmp7_);
	g_variant_ref_sink (_tmp8_);
	g_hash_table_insert (_tmp4_, _tmp5_, _tmp8_);
	_tmp9_ = self->priv->_renderer_hint;
	if (_tmp9_ != NULL) {
		GHashTable* _tmp10_ = NULL;
		gchar* _tmp11_ = NULL;
		const gchar* _tmp12_ = NULL;
		GVariant* _tmp13_ = NULL;
		_tmp10_ = self->priv->hints;
		_tmp11_ = g_strdup ("renderer-hint");
		_tmp12_ = self->priv->_renderer_hint;
		_tmp13_ = g_variant_new_string (_tmp12_);
		g_variant_ref_sink (_tmp13_);
		g_hash_table_insert (_tmp10_, _tmp11_, _tmp13_);
	}
	_tmp14_ = self->priv->hints;
	result = _tmp14_;
	return result;
}
