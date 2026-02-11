diodon_clipboard_model_get_item_by_checksum (DiodonClipboardModel* self, const gchar* checksum) {
	DiodonIClipboardItem* result = NULL;
	{
		GeeList* _item_list = NULL;
		GeeList* _tmp0_ = NULL;
		gint _item_size = 0;
		GeeList* _tmp1_ = NULL;
		gint _tmp2_ = 0;
		gint _tmp3_ = 0;
		gint _item_index = 0;
		_tmp0_ = diodon_clipboard_model_get_items (self);
		_item_list = _tmp0_;
		_tmp1_ = _item_list;
		_tmp2_ = gee_collection_get_size ((GeeCollection*) _tmp1_);
		_tmp3_ = _tmp2_;
		_item_size = _tmp3_;
		_item_index = -1;
		while (TRUE) {
			gint _tmp4_ = 0;
			gint _tmp5_ = 0;
			gint _tmp6_ = 0;
			DiodonIClipboardItem* item = NULL;
			GeeList* _tmp7_ = NULL;
			gint _tmp8_ = 0;
			gpointer _tmp9_ = NULL;
			GEqualFunc _tmp10_ = NULL;
			DiodonIClipboardItem* _tmp11_ = NULL;
			gchar* _tmp12_ = NULL;
			gchar* _tmp13_ = NULL;
			const gchar* _tmp14_ = NULL;
			gboolean _tmp15_ = FALSE;
			gboolean _tmp16_ = FALSE;
			_tmp4_ = _item_index;
			_item_index = _tmp4_ + 1;
			_tmp5_ = _item_index;
			_tmp6_ = _item_size;
			if (!(_tmp5_ < _tmp6_)) {
				break;
			}
			_tmp7_ = _item_list;
			_tmp8_ = _item_index;
			_tmp9_ = gee_list_get (_tmp7_, _tmp8_);
			item = (DiodonIClipboardItem*) _tmp9_;
			_tmp10_ = g_str_equal;
			_tmp11_ = item;
			_tmp12_ = diodon_iclipboard_item_get_checksum (_tmp11_);
			_tmp13_ = _tmp12_;
			_tmp14_ = checksum;
			_tmp15_ = _tmp10_ (_tmp13_, _tmp14_);
			_tmp16_ = _tmp15_;
			_g_free0 (_tmp13_);
			if (_tmp16_) {
				result = item;
				_g_object_unref0 (_item_list);
				return result;
			}
			_g_object_unref0 (item);
		}
		_g_object_unref0 (_item_list);
	}
	result = NULL;
	return result;
}
