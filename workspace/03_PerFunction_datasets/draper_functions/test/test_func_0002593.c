boxes_display_finalize (GObject* obj) {
	BoxesDisplay * self;
#line 4 "/extra-data/checkout/gnome/gnome-boxes/src/display.vala"
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, BOXES_TYPE_DISPLAY, BoxesDisplay);
#line 66 "/extra-data/checkout/gnome/gnome-boxes/src/display.vala"
	boxes_display_access_finish (self);
#line 8 "/extra-data/checkout/gnome/gnome-boxes/src/display.vala"
	_g_object_unref0 (self->priv->_config);
#line 13 "/extra-data/checkout/gnome/gnome-boxes/src/display.vala"
	_g_free0 (self->priv->_password);
#line 14 "/extra-data/checkout/gnome/gnome-boxes/src/display.vala"
	_g_free0 (self->priv->_username);
#line 39 "/extra-data/checkout/gnome/gnome-boxes/src/display.vala"
	_g_hash_table_unref0 (self->displays);
#line 4 "/extra-data/checkout/gnome/gnome-boxes/src/display.vala"
	G_OBJECT_CLASS (boxes_display_parent_class)->finalize (obj);
#line 831 "display.c"
}
