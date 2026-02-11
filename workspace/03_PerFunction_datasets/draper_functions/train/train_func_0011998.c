build_tool_set_description (BuildTool *self, const gchar* description) {
	const gchar* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	g_return_if_fail (description != NULL);
	_tmp0_ = description;
	_tmp1_ = g_strdup (_tmp0_);
	_g_free0 ((*self)._description);
	(*self)._description = _tmp1_;
}
