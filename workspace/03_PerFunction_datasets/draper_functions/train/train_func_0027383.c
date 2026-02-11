gmpc_browsers_metadata_real_browser_selected (GmpcPluginBrowserIface* base, GtkContainer* container) {
	GmpcBrowsersMetadata * self;
	gchar* artist = NULL;
	GtkContainer* _tmp0_;
	GtkPaned* _tmp1_;
	gchar* _tmp2_ = NULL;
	const gchar* _tmp3_;
	self = (GmpcBrowsersMetadata*) base;
	g_return_if_fail (container != NULL);
	self->priv->selected = TRUE;
	gmpc_browsers_metadata_browser_init (self);
	_tmp0_ = container;
	_tmp1_ = self->priv->paned;
	gtk_container_add (_tmp0_, (GtkWidget*) _tmp1_);
	_tmp2_ = gmpc_browsers_metadata_browser_get_selected_artist (self);
	_g_free0 (artist);
	artist = _tmp2_;
	_tmp3_ = artist;
	if (_tmp3_ == NULL) {
		gmpc_browsers_metadata_metadata_box_clear (self);
		gmpc_browsers_metadata_metadata_box_update (self);
	}
	_g_free0 (artist);
}
