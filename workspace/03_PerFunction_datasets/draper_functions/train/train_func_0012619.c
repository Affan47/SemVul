playlists_menuitem_finalize (GObject* obj) {
	PlaylistsMenuitem * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TYPE_PLAYLISTS_MENUITEM, PlaylistsMenuitem);
	_g_object_unref0 (self->priv->current_playlists);
	_g_object_unref0 (self->root_item);
	G_OBJECT_CLASS (playlists_menuitem_parent_class)->finalize (obj);
}
