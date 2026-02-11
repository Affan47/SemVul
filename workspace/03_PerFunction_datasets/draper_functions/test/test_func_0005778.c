skk_state_cancel_okuri (SkkState* self) {
	SkkRomKanaConverter* _tmp0_;
	SkkRomKanaConverter* _tmp1_;
	const gchar* _tmp2_;
	const gchar* _tmp3_;
	SkkRomKanaConverter* _tmp4_;
	const gchar* _tmp5_;
	const gchar* _tmp6_;
	gchar* _tmp7_;
	gchar* _tmp8_;
	SkkRomKanaConverter* _tmp9_;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->rom_kana_converter;
	_tmp1_ = self->rom_kana_converter;
	_tmp2_ = skk_rom_kana_converter_get_output (_tmp1_);
	_tmp3_ = _tmp2_;
	_tmp4_ = self->okuri_rom_kana_converter;
	_tmp5_ = skk_rom_kana_converter_get_output (_tmp4_);
	_tmp6_ = _tmp5_;
	_tmp7_ = g_strconcat (_tmp3_, _tmp6_, NULL);
	_tmp8_ = _tmp7_;
	skk_rom_kana_converter_set_output (_tmp1_, _tmp8_);
	_g_free0 (_tmp8_);
	_tmp9_ = self->okuri_rom_kana_converter;
	skk_rom_kana_converter_reset (_tmp9_);
	self->okuri = FALSE;
}
