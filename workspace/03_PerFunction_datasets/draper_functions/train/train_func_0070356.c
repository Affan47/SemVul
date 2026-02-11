gtkaml_markup_resolver_visit_markup_class (GtkamlMarkupResolver* self, GtkamlMarkupClass* mcl) {
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (mcl != NULL);
	{
		GtkamlMarkupClass* _tmp0_;
		GtkamlAstMarkupTag* _tmp1_;
		GtkamlAstMarkupTag* _tmp2_;
		GtkamlMarkupClass* _tmp3_;
		GtkamlAstMarkupTag* _tmp4_;
		GtkamlAstMarkupTag* _tmp5_;
		_tmp0_ = mcl;
		_tmp1_ = gtkaml_markupclass_get_markup_root (_tmp0_);
		_tmp2_ = _tmp1_;
		gtkaml_markup_resolver_resolve_markup_tag (self, _tmp2_, &_inner_error_);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == VALA_PARSE_ERROR) {
				goto __catch6_vala_parse_error;
			}
			g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
		_tmp3_ = mcl;
		_tmp4_ = gtkaml_markupclass_get_markup_root (_tmp3_);
		_tmp5_ = _tmp4_;
		gtkaml_markup_resolver_generate_markup_tag (self, _tmp5_, &_inner_error_);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == VALA_PARSE_ERROR) {
				goto __catch6_vala_parse_error;
			}
			g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
	}
	goto __finally6;
	__catch6_vala_parse_error:
	{
		GError* e = NULL;
		GError* _tmp6_;
		const gchar* _tmp7_;
		e = _inner_error_;
		_inner_error_ = NULL;
		_tmp6_ = e;
		_tmp7_ = _tmp6_->message;
		vala_report_error (NULL, _tmp7_);
		_g_error_free0 (e);
	}
	__finally6:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
}
