__lambda23_ (Desktop* self, GSimpleAction* action, GVariant* panel) {
	GVariant* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	g_return_if_fail (action != NULL);
	_tmp0_ = panel;
	_tmp1_ = g_variant_get_string (_tmp0_, NULL);
	desktop_show_settings (self, _tmp1_);
}
