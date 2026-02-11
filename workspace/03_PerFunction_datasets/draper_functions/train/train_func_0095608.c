skk_rom_kana_converter_is_valid (SkkRomKanaConverter* self, gunichar uc) {
	gboolean result = FALSE;
	gunichar _tmp0_;
	SkkRomKanaMapFile* _tmp1_;
	SkkRomKanaNode* _tmp2_;
	gunichar _tmp3_;
	gboolean _tmp4_;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp0_ = uc;
	if (_tmp0_ > ((gunichar) 128)) {
		result = FALSE;
		return result;
	}
	_tmp1_ = self->priv->_rule;
	_tmp2_ = _tmp1_->root_node;
	_tmp3_ = uc;
	_tmp4_ = _tmp2_->valid[(gint) _tmp3_];
	result = _tmp4_;
	return result;
}
