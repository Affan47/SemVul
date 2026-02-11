diodon_clipboard_model_get_last_item (DiodonClipboardModel* self) {
	DiodonIClipboardItem* result = NULL;
	DiodonIClipboardItem* item = NULL;
	gint _tmp0_ = 0;
	item = NULL;
	_tmp0_ = diodon_clipboard_model_get_size (self);
	if (_tmp0_ > 0) {
		GeeList* _tmp1_ = NULL;
		GeeList* _tmp2_ = NULL;
		gpointer _tmp3_ = NULL;
		_tmp1_ = diodon_clipboard_model_get_items (self);
		_tmp2_ = _tmp1_;
		_tmp3_ = gee_list_first (_tmp2_);
		_g_object_unref0 (item);
		item = (DiodonIClipboardItem*) _tmp3_;
		_g_object_unref0 (_tmp2_);
	}
	result = item;
	return result;
}
