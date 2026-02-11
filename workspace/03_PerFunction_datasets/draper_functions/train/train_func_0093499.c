boxes_sidebar_finalize (GObject* obj) {
	BoxesSidebar * self;
#line 12 "/extra-data/checkout/gnome/gnome-boxes/src/sidebar.vala"
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, BOXES_TYPE_SIDEBAR, BoxesSidebar);
#line 14 "/extra-data/checkout/gnome/gnome-boxes/src/sidebar.vala"
	_g_object_unref0 (self->notebook);
#line 18 "/extra-data/checkout/gnome/gnome-boxes/src/sidebar.vala"
	_g_object_unref0 (self->priv->bin_actor);
#line 19 "/extra-data/checkout/gnome/gnome-boxes/src/sidebar.vala"
	_g_object_unref0 (self->priv->gtk_actor);
#line 12 "/extra-data/checkout/gnome/gnome-boxes/src/sidebar.vala"
	G_OBJECT_CLASS (boxes_sidebar_parent_class)->finalize (obj);
#line 920 "sidebar.c"
}
