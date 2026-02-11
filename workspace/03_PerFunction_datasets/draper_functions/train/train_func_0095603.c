gtkaml_markup_hint_add_creation_method (GtkamlMarkupHint* self, const gchar* creation_method_name) {
	const gchar* _tmp0_;
	const gchar* _tmp1_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (creation_method_name != NULL);
	_tmp0_ = creation_method_name;
	_tmp1_ = gtkaml_markup_hint_NEW;
	gtkaml_markup_hint_add_hint (self, _tmp0_, _tmp1_);
}
