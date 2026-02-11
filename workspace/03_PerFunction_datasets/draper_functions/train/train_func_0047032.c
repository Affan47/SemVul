skk_state_finalize (GObject* obj) {
	SkkState * self;
	self = SKK_STATE (obj);
	skk_state_reset (self);
	_g_object_unref0 (self->dictionaries);
	_g_object_unref0 (self->candidates);
	_g_object_unref0 (self->rom_kana_converter);
	_g_object_unref0 (self->okuri_rom_kana_converter);
	_g_free0 (self->midasi);
	_g_string_free0 (self->output);
	_g_string_free0 (self->abbrev);
	_g_string_free0 (self->kuten);
	_g_object_unref0 (self->priv->completion);
	_g_object_unref0 (self->completion_iterator);
	self->auto_start_henkan_keywords = (_vala_array_free (self->auto_start_henkan_keywords, self->auto_start_henkan_keywords_length1, (GDestroyNotify) g_free), NULL);
	_g_free0 (self->auto_start_henkan_keyword);
	_g_object_unref0 (self->priv->_typing_rule);
	_g_regex_unref0 (self->priv->numeric_regex);
	_g_regex_unref0 (self->priv->numeric_ref_regex);
	_g_object_unref0 (self->surrounding_text);
	G_OBJECT_CLASS (skk_state_parent_class)->finalize (obj);
}
