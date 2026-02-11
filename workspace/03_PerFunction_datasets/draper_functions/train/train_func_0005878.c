unity_deprecated_scope_search_equals (UnityDeprecatedScopeSearch* self, UnityDeprecatedScopeSearch* other) {
	gboolean result = FALSE;
	gboolean _tmp0_ = FALSE;
	UnityDeprecatedScopeSearch* _tmp1_ = NULL;
	gboolean _tmp7_ = FALSE;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (other != NULL, FALSE);
	_tmp1_ = other;
	if (_tmp1_ == NULL) {
		_tmp0_ = TRUE;
	} else {
		const gchar* _tmp2_ = NULL;
		const gchar* _tmp3_ = NULL;
		UnityDeprecatedScopeSearch* _tmp4_ = NULL;
		const gchar* _tmp5_ = NULL;
		const gchar* _tmp6_ = NULL;
		_tmp2_ = unity_deprecated_scope_search_get_search_string (self);
		_tmp3_ = _tmp2_;
		_tmp4_ = other;
		_tmp5_ = unity_deprecated_scope_search_get_search_string (_tmp4_);
		_tmp6_ = _tmp5_;
		_tmp0_ = g_strcmp0 (_tmp3_, _tmp6_) != 0;
	}
	_tmp7_ = _tmp0_;
	if (_tmp7_) {
		result = FALSE;
		return result;
	}
	result = TRUE;
	return result;
}
