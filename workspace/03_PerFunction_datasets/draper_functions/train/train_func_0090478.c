caribou_scanner_set_mouse_button (CaribouScanner* self, gint value) {
	gint _tmp0_ = 0;
	g_return_if_fail (self != NULL);
	_tmp0_ = value;
	self->priv->_mouse_button = _tmp0_;
	caribou_scanner_configure_switch (self);
	g_object_notify ((GObject *) self, "mouse-button");
}
