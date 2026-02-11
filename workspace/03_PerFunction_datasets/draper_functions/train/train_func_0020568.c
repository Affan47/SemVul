gee_array_list_real_add (GeeAbstractCollection* base, gconstpointer item) {
	GeeArrayList * self;
	gboolean result = FALSE;
	gint _tmp0_ = 0;
	gpointer* _tmp1_ = NULL;
	gint _tmp1__length1 = 0;
	gpointer* _tmp2_ = NULL;
	gint _tmp2__length1 = 0;
	gint _tmp3_ = 0;
	gconstpointer _tmp4_ = NULL;
	gpointer _tmp5_ = NULL;
	gpointer _tmp6_ = NULL;
	gint _tmp7_ = 0;
	self = (GeeArrayList*) base;
	_tmp0_ = self->_size;
	_tmp1_ = self->_items;
	_tmp1__length1 = self->_items_length1;
	if (_tmp0_ == _tmp1__length1) {
		gee_array_list_grow_if_needed (self, 1);
	}
	_tmp2_ = self->_items;
	_tmp2__length1 = self->_items_length1;
	_tmp3_ = self->_size;
	self->_size = _tmp3_ + 1;
	_tmp4_ = item;
	_tmp5_ = ((_tmp4_ != NULL) && (self->priv->g_dup_func != NULL)) ? self->priv->g_dup_func ((gpointer) _tmp4_) : ((gpointer) _tmp4_);
	((_tmp2_[_tmp3_] == NULL) || (self->priv->g_destroy_func == NULL)) ? NULL : (_tmp2_[_tmp3_] = (self->priv->g_destroy_func (_tmp2_[_tmp3_]), NULL));
	_tmp2_[_tmp3_] = _tmp5_;
	_tmp6_ = _tmp2_[_tmp3_];
	_tmp7_ = self->priv->_stamp;
	self->priv->_stamp = _tmp7_ + 1;
	result = TRUE;
	return result;
}
