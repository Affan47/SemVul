boxes_editable_entry_finalize (GObject* obj) {
	BoxesEditableEntry * self;
#line 8 "/extra-data/checkout/gnome/gnome-boxes/src/editable-entry.vala"
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, BOXES_TYPE_EDITABLE_ENTRY, BoxesEditableEntry);
#line 17 "/extra-data/checkout/gnome/gnome-boxes/src/editable-entry.vala"
	_g_free0 (self->priv->_text);
#line 89 "/extra-data/checkout/gnome/gnome-boxes/src/editable-entry.vala"
	_g_object_unref0 (self->priv->notebook);
#line 90 "/extra-data/checkout/gnome/gnome-boxes/src/editable-entry.vala"
	_g_object_unref0 (self->priv->label);
#line 91 "/extra-data/checkout/gnome/gnome-boxes/src/editable-entry.vala"
	_g_object_unref0 (self->priv->button);
#line 92 "/extra-data/checkout/gnome/gnome-boxes/src/editable-entry.vala"
	_g_object_unref0 (self->priv->entry);
#line 8 "/extra-data/checkout/gnome/gnome-boxes/src/editable-entry.vala"
	G_OBJECT_CLASS (boxes_editable_entry_parent_class)->finalize (obj);
#line 1163 "editable-entry.c"
}
