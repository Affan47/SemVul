diodon_image_clipboard_item_construct_with_image (GType object_type, DiodonClipboardType clipboard_type, GdkPixbuf* pixbuf, GError** error) {
	DiodonImageClipboardItem * self = NULL;
	DiodonClipboardType _tmp0_ = 0;
	gchar* _tmp1_ = NULL;
	GdkPixbuf* _tmp2_ = NULL;
	gchar* _tmp3_ = NULL;
	GdkPixbuf* _tmp4_ = NULL;
	GError * _inner_error_ = NULL;
	self = (DiodonImageClipboardItem*) g_object_new (object_type, NULL);
	_tmp0_ = clipboard_type;
	self->priv->_clipboard_type = _tmp0_;
	_tmp2_ = pixbuf;
	_tmp3_ = diodon_image_clipboard_item_save_pixbuf (_tmp2_, &_inner_error_);
	_tmp1_ = _tmp3_;
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		_g_object_unref0 (self);
		return NULL;
	}
	_g_free0 (self->priv->_path);
	self->priv->_path = _tmp1_;
	_tmp4_ = pixbuf;
	diodon_image_clipboard_item_extract_pixbuf_info (self, _tmp4_);
	return self;
}
