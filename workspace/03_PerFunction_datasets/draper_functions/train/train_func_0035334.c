gtkaml_ast_markup_tag_strip_braces (GtkamlAstMarkupTag* self, const gchar* code, GError** error) {
	gchar* result = NULL;
	const gchar* _tmp0_;
	gchar* _tmp1_ = NULL;
	gchar* stripped_value;
	const gchar* _tmp2_;
	gboolean _tmp3_ = FALSE;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (code != NULL, NULL);
	_tmp0_ = code;
	_tmp1_ = string_strip (_tmp0_);
	stripped_value = _tmp1_;
	_tmp2_ = stripped_value;
	_tmp3_ = g_str_has_prefix (_tmp2_, "{");
	if (_tmp3_) {
		const gchar* _tmp4_;
		gboolean _tmp5_ = FALSE;
		_tmp4_ = stripped_value;
		_tmp5_ = g_str_has_suffix (_tmp4_, "}");
		if (_tmp5_) {
			const gchar* _tmp6_;
			const gchar* _tmp7_;
			gint _tmp8_;
			gint _tmp9_;
			gchar* _tmp10_ = NULL;
			_tmp6_ = stripped_value;
			_tmp7_ = stripped_value;
			_tmp8_ = strlen (_tmp7_);
			_tmp9_ = _tmp8_;
			_tmp10_ = string_substring (_tmp6_, (glong) 1, (glong) (_tmp9_ - 2));
			result = _tmp10_;
			_g_free0 (stripped_value);
			return result;
		} else {
			GError* _tmp11_;
			_tmp11_ = g_error_new_literal (VALA_PARSE_ERROR, VALA_PARSE_ERROR_SYNTAX, "Unbalanced braces");
			_inner_error_ = _tmp11_;
			if (_inner_error_->domain == VALA_PARSE_ERROR) {
				g_propagate_error (error, _inner_error_);
				_g_free0 (stripped_value);
				return NULL;
			} else {
				_g_free0 (stripped_value);
				g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
				g_clear_error (&_inner_error_);
				return NULL;
			}
		}
	} else {
		const gchar* _tmp12_;
		gchar* _tmp13_;
		_tmp12_ = code;
		_tmp13_ = g_strdup (_tmp12_);
		result = _tmp13_;
		_g_free0 (stripped_value);
		return result;
	}
	_g_free0 (stripped_value);
}
