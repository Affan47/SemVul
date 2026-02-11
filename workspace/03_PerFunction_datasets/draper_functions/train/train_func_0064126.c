unity_internal_aggregator_scope_impl_real_open_channel_data_free (gpointer _data) {
	UnityInternalAggregatorScopeImplOpenChannelData* _data_;
	_data_ = _data;
	_g_hash_table_unref0 (_data_->hints);
	_g_object_unref0 (_data_->cancellable);
	_g_free0 (_data_->sender);
	_g_free0 (_data_->result);
	_g_object_unref0 (_data_->self);
	g_slice_free (UnityInternalAggregatorScopeImplOpenChannelData, _data_);
}
