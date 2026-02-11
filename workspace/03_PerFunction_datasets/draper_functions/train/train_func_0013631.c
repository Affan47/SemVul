boxes_installer_media_get_device_from_path (BoxesInstallerMedia* self, const gchar* path, GUdevClient* client, GCancellable* cancellable, GAsyncReadyCallback _callback_, gpointer _user_data_) {
	BoxesInstallerMediaGetDeviceFromPathData* _data_;
	BoxesInstallerMedia* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	gchar* _tmp2_ = NULL;
	GUdevClient* _tmp3_ = NULL;
	GUdevClient* _tmp4_ = NULL;
	GCancellable* _tmp5_ = NULL;
	GCancellable* _tmp6_ = NULL;
#line 7 "/extra-data/checkout/gnome/gnome-boxes/src/installer-media.vala"
	_data_ = g_slice_new0 (BoxesInstallerMediaGetDeviceFromPathData);
#line 7 "/extra-data/checkout/gnome/gnome-boxes/src/installer-media.vala"
	_data_->_async_result = g_simple_async_result_new (G_OBJECT (self), _callback_, _user_data_, boxes_installer_media_get_device_from_path);
#line 7 "/extra-data/checkout/gnome/gnome-boxes/src/installer-media.vala"
	g_simple_async_result_set_op_res_gpointer (_data_->_async_result, _data_, boxes_installer_media_get_device_from_path_data_free);
#line 7 "/extra-data/checkout/gnome/gnome-boxes/src/installer-media.vala"
	_tmp0_ = _g_object_ref0 (self);
#line 7 "/extra-data/checkout/gnome/gnome-boxes/src/installer-media.vala"
	_data_->self = _tmp0_;
#line 7 "/extra-data/checkout/gnome/gnome-boxes/src/installer-media.vala"
	_tmp1_ = path;
#line 7 "/extra-data/checkout/gnome/gnome-boxes/src/installer-media.vala"
	_tmp2_ = g_strdup (_tmp1_);
#line 7 "/extra-data/checkout/gnome/gnome-boxes/src/installer-media.vala"
	_g_free0 (_data_->path);
#line 7 "/extra-data/checkout/gnome/gnome-boxes/src/installer-media.vala"
	_data_->path = _tmp2_;
#line 7 "/extra-data/checkout/gnome/gnome-boxes/src/installer-media.vala"
	_tmp3_ = client;
#line 7 "/extra-data/checkout/gnome/gnome-boxes/src/installer-media.vala"
	_tmp4_ = _g_object_ref0 (_tmp3_);
#line 7 "/extra-data/checkout/gnome/gnome-boxes/src/installer-media.vala"
	_g_object_unref0 (_data_->client);
#line 7 "/extra-data/checkout/gnome/gnome-boxes/src/installer-media.vala"
	_data_->client = _tmp4_;
#line 7 "/extra-data/checkout/gnome/gnome-boxes/src/installer-media.vala"
	_tmp5_ = cancellable;
#line 7 "/extra-data/checkout/gnome/gnome-boxes/src/installer-media.vala"
	_tmp6_ = _g_object_ref0 (_tmp5_);
#line 7 "/extra-data/checkout/gnome/gnome-boxes/src/installer-media.vala"
	_g_object_unref0 (_data_->cancellable);
#line 7 "/extra-data/checkout/gnome/gnome-boxes/src/installer-media.vala"
	_data_->cancellable = _tmp6_;
#line 7 "/extra-data/checkout/gnome/gnome-boxes/src/installer-media.vala"
	boxes_installer_media_get_device_from_path_co (_data_);
#line 1499 "installer-media.c"
}
