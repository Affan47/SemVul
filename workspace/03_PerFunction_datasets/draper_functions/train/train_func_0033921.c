skk_map_file_construct (GType object_type, SkkRuleMetadata* metadata, const gchar* type, const gchar* name, GError** error) {
	SkkMapFile * self = NULL;
	GeeHashSet* _tmp0_;
	GeeSet* included;
	SkkRuleMetadata _tmp1_;
	const gchar* _tmp2_;
	const gchar* _tmp3_;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (metadata != NULL, NULL);
	g_return_val_if_fail (type != NULL, NULL);
	g_return_val_if_fail (name != NULL, NULL);
	self = (SkkMapFile*) g_object_new (object_type, NULL);
	_tmp0_ = gee_hash_set_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, NULL, NULL);
	included = (GeeSet*) _tmp0_;
	_tmp1_ = *metadata;
	_tmp2_ = type;
	_tmp3_ = name;
	skk_map_file_load (self, &_tmp1_, _tmp2_, _tmp3_, included, &_inner_error_);
	if (_inner_error_ != NULL) {
		if (_inner_error_->domain == SKK_RULE_PARSE_ERROR) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (included);
			_g_object_unref0 (self);
			return NULL;
		} else {
			_g_object_unref0 (included);
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	_g_object_unref0 (included);
	return self;
}
