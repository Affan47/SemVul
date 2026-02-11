click_relevant_app_construct (GType object_type, const gchar* package, const gchar* version, const gchar* app_name, const gchar* user_name, const gchar* relative_path) {
	ClickRelevantApp * self = NULL;
	const gchar* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	const gchar* _tmp3_ = NULL;
	const gchar* _tmp4_ = NULL;
	g_return_val_if_fail (package != NULL, NULL);
	g_return_val_if_fail (version != NULL, NULL);
	g_return_val_if_fail (app_name != NULL, NULL);
	g_return_val_if_fail (relative_path != NULL, NULL);
	_tmp0_ = package;
	_tmp1_ = version;
	_tmp2_ = app_name;
	_tmp3_ = user_name;
	_tmp4_ = relative_path;
	self = (ClickRelevantApp*) g_object_new (object_type, "package", _tmp0_, "version", _tmp1_, "app-name", _tmp2_, "user-name", _tmp3_, "relative-path", _tmp4_, NULL);
	return self;
}
