edsf_memory_icon_real_equal (GIcon* base, GIcon* icon2) {
	EdsfMemoryIcon * self;
	gboolean result = FALSE;
	EdsfMemoryIcon* icon = NULL;
	GIcon* _tmp0_ = NULL;
	EdsfMemoryIcon* _tmp1_ = NULL;
	gboolean _tmp2_ = FALSE;
	guint8* _tmp3_ = NULL;
	gint _tmp3__length1 = 0;
	EdsfMemoryIcon* _tmp4_ = NULL;
	guint8* _tmp5_ = NULL;
	gint _tmp5__length1 = 0;
	gboolean _tmp11_ = FALSE;
	self = (EdsfMemoryIcon*) base;
	_tmp0_ = icon2;
	_tmp1_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_CAST (G_TYPE_CHECK_INSTANCE_CAST (_tmp0_, G_TYPE_ICON, GIcon), EDSF_TYPE_MEMORY_ICON, EdsfMemoryIcon));
	icon = _tmp1_;
	_tmp3_ = self->priv->_image_data;
	_tmp3__length1 = self->priv->_image_data_length1;
	_tmp4_ = icon;
	_tmp5_ = _tmp4_->priv->_image_data;
	_tmp5__length1 = _tmp4_->priv->_image_data_length1;
	if (_tmp3__length1 == _tmp5__length1) {
		guint8* _tmp6_ = NULL;
		gint _tmp6__length1 = 0;
		EdsfMemoryIcon* _tmp7_ = NULL;
		guint8* _tmp8_ = NULL;
		gint _tmp8__length1 = 0;
		guint8* _tmp9_ = NULL;
		gint _tmp9__length1 = 0;
		gint _tmp10_ = 0;
		_tmp6_ = self->priv->_image_data;
		_tmp6__length1 = self->priv->_image_data_length1;
		_tmp7_ = icon;
		_tmp8_ = _tmp7_->priv->_image_data;
		_tmp8__length1 = _tmp7_->priv->_image_data_length1;
		_tmp9_ = self->priv->_image_data;
		_tmp9__length1 = self->priv->_image_data_length1;
		_tmp10_ = memcmp (_tmp6_, _tmp8_, (gsize) _tmp9__length1);
		_tmp2_ = _tmp10_ == 0;
	} else {
		_tmp2_ = FALSE;
	}
	_tmp11_ = _tmp2_;
	result = _tmp11_;
	_g_object_unref0 (icon);
	return result;
}
