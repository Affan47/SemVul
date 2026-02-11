unity_application_preview_construct (GType object_type, const gchar* title, const gchar* subtitle, const gchar* description, GIcon* icon, GIcon* screenshot) {
	UnityApplicationPreview * self = NULL;
	const gchar* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	GIcon* _tmp2_ = NULL;
	const gchar* _tmp3_ = NULL;
	GIcon* _tmp4_ = NULL;
	g_return_val_if_fail (title != NULL, NULL);
	g_return_val_if_fail (subtitle != NULL, NULL);
	g_return_val_if_fail (description != NULL, NULL);
	_tmp0_ = title;
	_tmp1_ = subtitle;
	_tmp2_ = screenshot;
	_tmp3_ = description;
	_tmp4_ = icon;
	self = (UnityApplicationPreview*) g_object_new (object_type, "title", _tmp0_, "subtitle", _tmp1_, "image", _tmp2_, "description-markup", _tmp3_, "app-icon", _tmp4_, NULL);
	return self;
}
