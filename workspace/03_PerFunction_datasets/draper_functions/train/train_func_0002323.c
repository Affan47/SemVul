edsf_memory_icon_real_load (GLoadableIcon* base, gint size, gchar** type, GCancellable* cancellable, GError** error) {
	EdsfMemoryIcon * self;
	gchar* _vala_type = NULL;
	GInputStream* result = NULL;
	const gchar* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	guint8* _tmp2_ = NULL;
	gint _tmp2__length1 = 0;
	guint8* _tmp3_ = NULL;
	gint _tmp3__length1 = 0;
	GMemoryInputStream* _tmp4_ = NULL;
	self = (EdsfMemoryIcon*) base;
	_tmp0_ = self->priv->_image_type;
	_tmp1_ = g_strdup (_tmp0_);
	_g_free0 (_vala_type);
	_vala_type = _tmp1_;
	_tmp2_ = self->priv->_image_data;
	_tmp2__length1 = self->priv->_image_data_length1;
	_tmp3_ = (_tmp2_ != NULL) ? _vala_array_dup3 (_tmp2_, _tmp2__length1) : ((gpointer) _tmp2_);
	_tmp3__length1 = _tmp2__length1;
	_tmp4_ = (GMemoryInputStream*) g_memory_input_stream_new_from_data (_tmp3_, _tmp3__length1, _g_free_gdestroy_notify);
	result = (GInputStream*) _tmp4_;
	if (type) {
		*type = _vala_type;
	} else {
		_g_free0 (_vala_type);
	}
	return result;
}
