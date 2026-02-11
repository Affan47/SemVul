unity_internal_aggregator_scope_impl_on_results_invalidated (UnityInternalAggregatorScopeImpl* self, UnityInternalChannelUpdateFlags flags) {
	UnityInternalChannelUpdateFlags _tmp0_ = 0;
	UnityInternalChannelUpdateFlags _tmp4_ = 0;
	g_return_if_fail (self != NULL);
	_tmp0_ = flags;
	if ((_tmp0_ & UNITY_INTERNAL_CHANNEL_UPDATE_FLAGS_DEFAULT) == UNITY_INTERNAL_CHANNEL_UPDATE_FLAGS_DEFAULT) {
		UnityProtocolChannelType channel_type = 0;
		UnityProtocolChannelType _tmp1_ = 0;
		gboolean _tmp2_ = FALSE;
		channel_type = UNITY_PROTOCOL_CHANNEL_TYPE_DEFAULT;
		_tmp1_ = channel_type;
		_tmp2_ = unity_internal_aggregator_scope_impl_invalidate_last_search_for_channel (self, _tmp1_);
		if (_tmp2_) {
			UnityProtocolChannelType _tmp3_ = 0;
			_tmp3_ = channel_type;
			g_signal_emit_by_name ((UnityProtocolScopeService*) self, "results-invalidated", (guint) _tmp3_);
		}
	}
	_tmp4_ = flags;
	if ((_tmp4_ & UNITY_INTERNAL_CHANNEL_UPDATE_FLAGS_GLOBAL) == UNITY_INTERNAL_CHANNEL_UPDATE_FLAGS_GLOBAL) {
		UnityProtocolChannelType channel_type = 0;
		UnityProtocolChannelType _tmp5_ = 0;
		gboolean _tmp6_ = FALSE;
		channel_type = UNITY_PROTOCOL_CHANNEL_TYPE_GLOBAL;
		_tmp5_ = channel_type;
		_tmp6_ = unity_internal_aggregator_scope_impl_invalidate_last_search_for_channel (self, _tmp5_);
		if (_tmp6_) {
			UnityProtocolChannelType _tmp7_ = 0;
			_tmp7_ = channel_type;
			g_signal_emit_by_name ((UnityProtocolScopeService*) self, "results-invalidated", (guint) _tmp7_);
		}
	}
}
