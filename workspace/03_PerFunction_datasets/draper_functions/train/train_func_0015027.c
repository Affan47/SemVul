gmpc_browsers_metadata_hitem_finalize (GmpcBrowsersMetadataHitem* obj) {
	GmpcBrowsersMetadataHitem * self;
	self = GMPC_BROWSERS_METADATA_HITEM (obj);
	_mpd_freeSong0 (self->song);
	_g_free0 (self->search_string);
}
