boxes_editable_entry_stop_editing (BoxesEditableEntry* self) {
	gboolean _tmp0_ = FALSE;
	GtkNotebook* _tmp1_ = NULL;
	GtkEntry* _tmp2_ = NULL;
	const gchar* _tmp3_ = NULL;
	const gchar* _tmp4_ = NULL;
#line 129 "/extra-data/checkout/gnome/gnome-boxes/src/editable-entry.vala"
	g_return_if_fail (self != NULL);
#line 132 "/extra-data/checkout/gnome/gnome-boxes/src/editable-entry.vala"
	_tmp0_ = self->priv->in_stop_editing;
#line 132 "/extra-data/checkout/gnome/gnome-boxes/src/editable-entry.vala"
	if (_tmp0_) {
#line 133 "/extra-data/checkout/gnome/gnome-boxes/src/editable-entry.vala"
		return;
#line 389 "editable-entry.c"
	}
#line 135 "/extra-data/checkout/gnome/gnome-boxes/src/editable-entry.vala"
	self->priv->in_stop_editing = TRUE;
#line 136 "/extra-data/checkout/gnome/gnome-boxes/src/editable-entry.vala"
	_tmp1_ = self->priv->notebook;
#line 136 "/extra-data/checkout/gnome/gnome-boxes/src/editable-entry.vala"
	g_object_set (_tmp1_, "page", (gint) BOXES_EDITABLE_ENTRY_PAGE_BUTTON, NULL);
#line 137 "/extra-data/checkout/gnome/gnome-boxes/src/editable-entry.vala"
	_tmp2_ = self->priv->entry;
#line 137 "/extra-data/checkout/gnome/gnome-boxes/src/editable-entry.vala"
	_tmp3_ = gtk_entry_get_text (_tmp2_);
#line 137 "/extra-data/checkout/gnome/gnome-boxes/src/editable-entry.vala"
	_tmp4_ = _tmp3_;
#line 137 "/extra-data/checkout/gnome/gnome-boxes/src/editable-entry.vala"
	boxes_editable_entry_set_text (self, _tmp4_);
#line 138 "/extra-data/checkout/gnome/gnome-boxes/src/editable-entry.vala"
	g_signal_emit_by_name (self, "editing-done");
#line 139 "/extra-data/checkout/gnome/gnome-boxes/src/editable-entry.vala"
	self->priv->in_stop_editing = FALSE;
#line 409 "editable-entry.c"
}
