gtkaml_markup_parser_parse_using_directives (GtkamlMarkupParser* self, GtkamlMarkupScanner* scanner, ValaNamespace* ns_current, GError** error) {
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (scanner != NULL);
	g_return_if_fail (ns_current != NULL);
	{
		GtkamlMarkupScanner* _tmp0_;
		xmlNode* _tmp1_;
		xmlNs* _tmp2_;
		xmlNs* ns;
		_tmp0_ = scanner;
		_tmp1_ = _tmp0_->node;
		_tmp2_ = _tmp1_->nsDef;
		ns = _tmp2_;
		{
			gboolean _tmp3_;
			_tmp3_ = TRUE;
			while (TRUE) {
				gboolean _tmp4_;
				xmlNs* _tmp7_;
				xmlNs* _tmp8_;
				const gchar* _tmp9_;
				GtkamlMarkupScanner* _tmp10_;
				const gchar* _tmp11_;
				const gchar* _tmp12_;
				_tmp4_ = _tmp3_;
				if (!_tmp4_) {
					xmlNs* _tmp5_;
					xmlNs* _tmp6_;
					_tmp5_ = ns;
					_tmp6_ = _tmp5_->next;
					ns = _tmp6_;
				}
				_tmp3_ = FALSE;
				_tmp7_ = ns;
				if (!(_tmp7_ != NULL)) {
					break;
				}
				_tmp8_ = ns;
				_tmp9_ = _tmp8_->href;
				_tmp10_ = scanner;
				_tmp11_ = gtkaml_markup_scanner_get_gtkaml_uri (_tmp10_);
				_tmp12_ = _tmp11_;
				if (g_strcmp0 (_tmp9_, _tmp12_) != 0) {
					GtkamlMarkupScanner* _tmp13_;
					xmlNs* _tmp14_;
					const gchar* _tmp15_;
					ValaNamespace* _tmp16_;
					_tmp13_ = scanner;
					_tmp14_ = ns;
					_tmp15_ = _tmp14_->href;
					_tmp16_ = ns_current;
					gtkaml_markup_parser_parse_using_directive (self, _tmp13_, _tmp15_, _tmp16_, &_inner_error_);
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
			}
		}
	}
}
