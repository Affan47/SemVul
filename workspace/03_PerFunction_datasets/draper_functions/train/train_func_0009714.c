metadata_menuitem_alter_label (MetadataMenuitem* self, const gchar* new_title) {
	const gchar* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = new_title;
	if (_tmp0_ == NULL) {
		return;
	}
	_tmp1_ = new_title;
	dbusmenu_menuitem_property_set ((DbusmenuMenuitem*) self, DBUSMENU_METADATA_MENUITEM_PLAYER_NAME, _tmp1_);
}
