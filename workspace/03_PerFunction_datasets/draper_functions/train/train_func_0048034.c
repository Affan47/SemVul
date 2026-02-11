boxes_search_provider_app_real_startup (GApplication* base) {
	BoxesSearchProviderApp * self;
	const gchar* _tmp0_ = NULL;
#line 195 "/extra-data/checkout/gnome/gnome-boxes/src/gnome-boxes-search-provider.vala"
	self = (BoxesSearchProviderApp*) base;
#line 196 "/extra-data/checkout/gnome/gnome-boxes/src/gnome-boxes-search-provider.vala"
	_tmp0_ = g_getenv ("BOXES_SEARCH_PROVIDER_PERSIST");
#line 196 "/extra-data/checkout/gnome/gnome-boxes/src/gnome-boxes-search-provider.vala"
	if (_tmp0_ != NULL) {
#line 197 "/extra-data/checkout/gnome/gnome-boxes/src/gnome-boxes-search-provider.vala"
		g_application_hold ((GApplication*) self);
#line 3928 "gnome-boxes-search-provider.c"
	}
#line 198 "/extra-data/checkout/gnome/gnome-boxes/src/gnome-boxes-search-provider.vala"
	G_APPLICATION_CLASS (boxes_search_provider_app_parent_class)->startup (G_TYPE_CHECK_INSTANCE_CAST (self, g_application_get_type (), GApplication));
#line 3932 "gnome-boxes-search-provider.c"
}
