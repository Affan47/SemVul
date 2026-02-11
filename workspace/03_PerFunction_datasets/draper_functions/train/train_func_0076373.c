property_panel_set_auxiliary_text (PropertyPanel* self, IBusText* text) {
	IBusText* _tmp0_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = text;
	if (_tmp0_ == NULL) {
		return;
	}
	g_debug ("propertypanel.vala:144: set_auxiliary_text(text)\n");
	property_panel_hide_if_necessary (self);
}
