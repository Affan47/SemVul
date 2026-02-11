unity_aggregated_scope_search_push_filter_settings (UnityAggregatedScopeSearch* self, UnityFilterSet* filters) {
	UnitySearchContext* _tmp0_ = NULL;
	UnityCancellable* _tmp1_ = NULL;
	gboolean _tmp2_ = FALSE;
	UnityAggregatorScope* agg_scope = NULL;
	UnityDeprecatedScopeBase* _tmp3_ = NULL;
	UnityDeprecatedScopeBase* _tmp4_ = NULL;
	UnityAggregatorScope* _tmp5_ = NULL;
	UnityAggregatorScope* _tmp6_ = NULL;
	const gchar* _tmp7_ = NULL;
	const gchar* _tmp8_ = NULL;
	UnityFilterSet* _tmp9_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (filters != NULL);
	_tmp0_ = ((UnityScopeSearchBase*) self)->search_context;
	_tmp1_ = (*_tmp0_).cancellable;
	_tmp2_ = unity_cancellable_is_cancelled (_tmp1_);
	if (_tmp2_) {
		return;
	}
	_tmp3_ = unity_deprecated_scope_search_get_owner ((UnityDeprecatedScopeSearch*) self);
	_tmp4_ = _tmp3_;
	_tmp5_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_TYPE (_tmp4_, UNITY_TYPE_AGGREGATOR_SCOPE) ? ((UnityAggregatorScope*) _tmp4_) : NULL);
	agg_scope = _tmp5_;
	_tmp6_ = agg_scope;
	_tmp7_ = unity_deprecated_scope_search_get_channel_id ((UnityDeprecatedScopeSearch*) self);
	_tmp8_ = _tmp7_;
	_tmp9_ = filters;
	unity_aggregator_scope_push_filter_settings (_tmp6_, _tmp8_, _tmp9_);
	_g_object_unref0 (agg_scope);
}
