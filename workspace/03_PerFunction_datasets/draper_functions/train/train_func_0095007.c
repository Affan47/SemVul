alm_privacy_widget_finalize (GObject* obj) {
	AlmPrivacyWidget * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, ALM_TYPE_PRIVACY_WIDGET, AlmPrivacyWidget);
	_alm_blacklist_unref0 (self->priv->blacklist);
	_alm_file_type_blacklist_unref0 (self->priv->files_type_blacklist);
	_alm_path_blacklist_unref0 (self->priv->path_blacklist);
	_g_object_unref0 (self->priv->mime_dict);
	_g_object_unref0 (self->priv->checkboxes);
	_g_object_unref0 (self->priv->button_list);
	_g_object_unref0 (self->priv->defined_dirs);
	_alm_application_blacklist_unref0 (self->priv->app_blacklist);
	_g_object_unref0 (self->priv->app_dialog);
	_g_object_unref0 (self->priv->app_treeview);
	_g_object_unref0 (self->priv->container_box);
	_g_hash_table_unref0 (self->priv->blocked_list);
	_g_hash_table_unref0 (self->priv->unblocked_list);
	_g_object_unref0 (self->priv->exception_list);
	_g_object_unref0 (self->priv->exception_list_store);
	_g_object_unref0 (self->priv->record_button);
	_g_object_unref0 (self->priv->del_button);
	_g_object_unref0 (self->priv->delete_dialog);
	_g_object_unref0 (self->priv->stock_folder_icon);
	_g_object_unref0 (self->priv->exception_menu);
	_g_object_unref0 (self->priv->privacy_settings);
	G_OBJECT_CLASS (alm_privacy_widget_parent_class)->finalize (obj);
}
