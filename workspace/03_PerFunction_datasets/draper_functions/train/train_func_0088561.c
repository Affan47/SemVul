__lambda9_ (Block16Data* _data16_, DeeModel* orig_model, DeeModelIter* iter, DeeFilterModel* filter_model) {
	gboolean result = FALSE;
	GVariant* metadata = NULL;
	DeeModel* _tmp0_ = NULL;
	DeeModelIter* _tmp1_ = NULL;
	GVariant* _tmp2_ = NULL;
	const gchar* field_name = NULL;
	const GVariantType* schema = NULL;
	GHashTableIter ht_iter = {0};
	DeeFilterModel* _tmp12_ = NULL;
	DeeModelIter* _tmp13_ = NULL;
	g_return_val_if_fail (orig_model != NULL, FALSE);
	g_return_val_if_fail (iter != NULL, FALSE);
	g_return_val_if_fail (filter_model != NULL, FALSE);
	_tmp0_ = orig_model;
	_tmp1_ = iter;
	_tmp2_ = dee_model_get_value (_tmp0_, _tmp1_, UNITY_INTERNAL_SCOPE_CHANNEL_METADATA_COLUMN);
	metadata = _tmp2_;
	g_hash_table_iter_init (&ht_iter, _data16_->types);
	while (TRUE) {
		gconstpointer _tmp3_ = NULL;
		gconstpointer _tmp4_ = NULL;
		gboolean _tmp5_ = FALSE;
		GVariant* field = NULL;
		GVariant* _tmp6_ = NULL;
		const gchar* _tmp7_ = NULL;
		const GVariantType* _tmp8_ = NULL;
		GVariant* _tmp9_ = NULL;
		GVariant* _tmp10_ = NULL;
		_tmp5_ = g_hash_table_iter_next (&ht_iter, (gpointer*) (&_tmp3_), (gpointer*) (&_tmp4_));
		field_name = _tmp3_;
		schema = _tmp4_;
		if (!_tmp5_) {
			break;
		}
		_tmp6_ = metadata;
		_tmp7_ = field_name;
		_tmp8_ = schema;
		_tmp9_ = g_variant_lookup_value (_tmp6_, _tmp7_, _tmp8_);
		field = _tmp9_;
		_tmp10_ = field;
		if (_tmp10_ == NULL) {
			const gchar* _tmp11_ = NULL;
			_tmp11_ = field_name;
			g_warning ("unity-scope-channel.vala:109: Row doesn't contain required data: missi" \
"ng '%s'", _tmp11_);
			result = FALSE;
			_g_variant_unref0 (field);
			_g_variant_unref0 (metadata);
			return result;
		}
		_g_variant_unref0 (field);
	}
	_tmp12_ = filter_model;
	_tmp13_ = iter;
	dee_filter_model_insert_iter_with_original_order (_tmp12_, _tmp13_);
	result = TRUE;
	_g_variant_unref0 (metadata);
	return result;
}
