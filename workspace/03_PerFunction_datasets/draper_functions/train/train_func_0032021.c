gtkaml_ast_markup_reference_real_resolve_attributes (GtkamlAstMarkupTag* base, GtkamlMarkupResolver* resolver, GError** error) {
	GtkamlAstMarkupReference * self;
	GtkamlMarkupResolver* _tmp0_;
	GError * _inner_error_ = NULL;
	self = (GtkamlAstMarkupReference*) base;
	g_return_if_fail (resolver != NULL);
	_tmp0_ = resolver;
	gtkaml_ast_markup_child_tag_resolve_composition_method ((GtkamlAstMarkupChildTag*) self, _tmp0_, &_inner_error_);
	if (_inner_error_ != NULL) {
		if (_inner_error_->domain == VALA_PARSE_ERROR) {
			g_propagate_error (error, _inner_error_);
			return;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
	}
}
