__lambda142_ (AppSettings* self, GSettings* setting, const gchar* key) {
	guint val = 0U;
	GSettings* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	g_return_if_fail (setting != NULL);
	g_return_if_fail (key != NULL);
	_tmp0_ = setting;
	_tmp1_ = key;
	g_settings_get (_tmp0_, _tmp1_, "u", &val);
	{
		GeeList* _view_list = NULL;
		Latexila* _tmp2_ = NULL;
		Latexila* _tmp3_ = NULL;
		GeeList* _tmp4_ = NULL;
		GeeList* _tmp5_ = NULL;
		gint _view_size = 0;
		GeeList* _tmp6_ = NULL;
		gint _tmp7_ = 0;
		gint _tmp8_ = 0;
		gint _view_index = 0;
		_tmp2_ = latexila_get_instance ();
		_tmp3_ = _tmp2_;
		_tmp4_ = latexila_get_views (_tmp3_);
		_tmp5_ = _tmp4_;
		_g_object_unref0 (_tmp3_);
		_view_list = _tmp5_;
		_tmp6_ = _view_list;
		_tmp7_ = gee_collection_get_size ((GeeCollection*) _tmp6_);
		_tmp8_ = _tmp7_;
		_view_size = _tmp8_;
		_view_index = -1;
		while (TRUE) {
			gint _tmp9_ = 0;
			gint _tmp10_ = 0;
			gint _tmp11_ = 0;
			DocumentView* view = NULL;
			GeeList* _tmp12_ = NULL;
			gint _tmp13_ = 0;
			gpointer _tmp14_ = NULL;
			DocumentView* _tmp15_ = NULL;
			guint _tmp16_ = 0U;
			_tmp9_ = _view_index;
			_view_index = _tmp9_ + 1;
			_tmp10_ = _view_index;
			_tmp11_ = _view_size;
			if (!(_tmp10_ < _tmp11_)) {
				break;
			}
			_tmp12_ = _view_list;
			_tmp13_ = _view_index;
			_tmp14_ = gee_list_get (_tmp12_, _tmp13_);
			view = (DocumentView*) _tmp14_;
			_tmp15_ = view;
			_tmp16_ = val;
			gtk_source_view_set_tab_width ((GtkSourceView*) _tmp15_, _tmp16_);
			_g_object_unref0 (view);
		}
		_g_object_unref0 (_view_list);
	}
}
