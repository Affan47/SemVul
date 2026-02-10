zeitgeist_data_source_registry_extension_real_register_data_source_data_free (gpointer _data) {
	ZeitgeistDataSourceRegistryExtensionRegisterDataSourceData* _data_;
	_data_ = _data;
	_g_free0 (_data_->unique_id);
	_g_free0 (_data_->name);
	_g_free0 (_data_->description);
	_g_variant_unref0 (_data_->event_templates);
	_g_object_unref0 (_data_->cancellable);
	_g_free0 (_data_->sender);
	_g_object_unref0 (_data_->self);
	g_slice_free (ZeitgeistDataSourceRegistryExtensionRegisterDataSourceData, _data_);
}
