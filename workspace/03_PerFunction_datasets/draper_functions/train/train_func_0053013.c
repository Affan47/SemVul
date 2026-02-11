skk_rom_kana_map_file_construct (GType object_type, SkkRuleMetadata* metadata, GError** error) {
	SkkRomKanaMapFile * self = NULL;
	SkkRuleMetadata _tmp0_;
	gboolean _tmp1_ = FALSE;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (metadata != NULL, NULL);
	_tmp0_ = *metadata;
	self = (SkkRomKanaMapFile*) skk_map_file_construct (object_type, &_tmp0_, "rom-kana", "default", &_inner_error_);
	if (_inner_error_ != NULL) {
		if (_inner_error_->domain == SKK_RULE_PARSE_ERROR) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (self);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	_tmp1_ = skk_map_file_has_map ((SkkMapFile*) self, "rom-kana");
	if (_tmp1_) {
		GeeMap* _tmp2_ = NULL;
		GeeMap* _tmp3_;
		SkkRomKanaNode* _tmp4_ = NULL;
		SkkRomKanaNode* _tmp5_;
		SkkRomKanaNode* _tmp6_;
		_tmp2_ = skk_map_file_get ((SkkMapFile*) self, "rom-kana");
		_tmp3_ = _tmp2_;
		_tmp4_ = skk_rom_kana_map_file_parse_rule (self, _tmp3_, &_inner_error_);
		_tmp5_ = _tmp4_;
		_g_object_unref0 (_tmp3_);
		_tmp6_ = _tmp5_;
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == SKK_RULE_PARSE_ERROR) {
				g_propagate_error (error, _inner_error_);
				_g_object_unref0 (self);
				return NULL;
			} else {
				g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
				g_clear_error (&_inner_error_);
				return NULL;
			}
		}
		_g_object_unref0 (self->root_node);
		self->root_node = _tmp6_;
	} else {
		GError* _tmp7_;
		_tmp7_ = g_error_new_literal (SKK_RULE_PARSE_ERROR, SKK_RULE_PARSE_ERROR_FAILED, "no rom-kana entry");
		_inner_error_ = _tmp7_;
		if (_inner_error_->domain == SKK_RULE_PARSE_ERROR) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (self);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	return self;
}
