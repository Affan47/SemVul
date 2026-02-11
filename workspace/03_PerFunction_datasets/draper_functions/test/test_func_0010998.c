gtkaml_ast_markup_root_real_resolve_creation_method_failed (GtkamlAstMarkupTag* base, ValaSourceReference* source_reference, const gchar* message) {
	GtkamlAstMarkupRoot * self;
	ValaSourceReference* _tmp0_;
	const gchar* _tmp1_;
	self = (GtkamlAstMarkupRoot*) base;
	g_return_if_fail (source_reference != NULL);
	g_return_if_fail (message != NULL);
	_tmp0_ = source_reference;
	_tmp1_ = message;
	vala_report_warning (_tmp0_, _tmp1_);
}
