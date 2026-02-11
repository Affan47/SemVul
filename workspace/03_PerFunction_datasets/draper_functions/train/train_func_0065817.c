unity_internal_scope_tracker_get_scope_id_for_proxy (UnityInternalScopeTracker* self, UnityProtocolScopeProxy* proxy) {
	gchar* result = NULL;
	GHashTableIter iter = {0};
	GHashTable* _tmp0_ = NULL;
	const gchar* scope_id = NULL;
	UnityInternalUtilsAsyncOnce* val = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (proxy != NULL, NULL);
	_tmp0_ = self->priv->scope_proxies;
	g_hash_table_iter_init (&iter, _tmp0_);
	while (TRUE) {
		gconstpointer _tmp1_ = NULL;
		gconstpointer _tmp2_ = NULL;
		gboolean _tmp3_ = FALSE;
		UnityInternalUtilsAsyncOnce* _tmp4_ = NULL;
		gconstpointer _tmp5_ = NULL;
		UnityProtocolScopeProxy* _tmp6_ = NULL;
		_tmp3_ = g_hash_table_iter_next (&iter, (gpointer*) (&_tmp1_), (gpointer*) (&_tmp2_));
		scope_id = _tmp1_;
		val = _tmp2_;
		if (!_tmp3_) {
			break;
		}
		_tmp4_ = val;
		_tmp5_ = unity_internal_utils_async_once_get_data (_tmp4_);
		_tmp6_ = proxy;
		if (((UnityProtocolScopeProxy*) _tmp5_) == _tmp6_) {
			const gchar* _tmp7_ = NULL;
			gchar* _tmp8_ = NULL;
			_tmp7_ = scope_id;
			_tmp8_ = g_strdup (_tmp7_);
			result = _tmp8_;
			return result;
		}
	}
	result = NULL;
	return result;
}
