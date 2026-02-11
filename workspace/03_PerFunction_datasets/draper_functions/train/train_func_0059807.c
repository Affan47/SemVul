click_hook_remove (ClickHook* self, const gchar* user_name, GError** error) {
	GList* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	GList* _tmp2_ = NULL;
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp1_ = user_name;
	_tmp2_ = click_hook_get_relevant_apps (self, _tmp1_, &_inner_error_);
	_tmp0_ = _tmp2_;
	if (_inner_error_ != NULL) {
		g_propagate_error (error, _inner_error_);
		return;
	}
	{
		GList* app_collection = NULL;
		GList* app_it = NULL;
		app_collection = _tmp0_;
		for (app_it = app_collection; app_it != NULL; app_it = app_it->next) {
			ClickRelevantApp* _tmp3_ = NULL;
			ClickRelevantApp* app = NULL;
			_tmp3_ = _g_object_ref0 ((ClickRelevantApp*) app_it->data);
			app = _tmp3_;
			{
				ClickRelevantApp* _tmp4_ = NULL;
				const gchar* _tmp5_ = NULL;
				const gchar* _tmp6_ = NULL;
				ClickRelevantApp* _tmp7_ = NULL;
				const gchar* _tmp8_ = NULL;
				const gchar* _tmp9_ = NULL;
				ClickRelevantApp* _tmp10_ = NULL;
				const gchar* _tmp11_ = NULL;
				const gchar* _tmp12_ = NULL;
				ClickRelevantApp* _tmp13_ = NULL;
				const gchar* _tmp14_ = NULL;
				const gchar* _tmp15_ = NULL;
				_tmp4_ = app;
				_tmp5_ = click_relevant_app_get_package (_tmp4_);
				_tmp6_ = _tmp5_;
				_tmp7_ = app;
				_tmp8_ = click_relevant_app_get_version (_tmp7_);
				_tmp9_ = _tmp8_;
				_tmp10_ = app;
				_tmp11_ = click_relevant_app_get_app_name (_tmp10_);
				_tmp12_ = _tmp11_;
				_tmp13_ = app;
				_tmp14_ = click_relevant_app_get_user_name (_tmp13_);
				_tmp15_ = _tmp14_;
				click_hook_remove_package (self, _tmp6_, _tmp9_, _tmp12_, _tmp15_, &_inner_error_);
				if (_inner_error_ != NULL) {
					g_propagate_error (error, _inner_error_);
					_g_object_unref0 (app);
					__g_list_free__g_object_unref0_0 (app_collection);
					return;
				}
				_g_object_unref0 (app);
			}
		}
		__g_list_free__g_object_unref0_0 (app_collection);
	}
}
