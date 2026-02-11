metadata_menuitem_should_collapse (MetadataMenuitem* self, gboolean collapse) {
	gboolean _tmp0_ = FALSE;
	g_return_if_fail (self != NULL);
	_tmp0_ = collapse;
	dbusmenu_menuitem_property_set_bool ((DbusmenuMenuitem*) self, DBUSMENU_METADATA_MENUITEM_HIDE_TRACK_DETAILS, _tmp0_);
}
