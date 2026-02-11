boxes_collection_source_construct_with_file (GType object_type, const gchar* filename, GError** error) {
	BoxesCollectionSource * self = NULL;
	const gchar* _tmp0_ = NULL;
	GError * _inner_error_ = NULL;
#line 116 "/extra-data/checkout/gnome/gnome-boxes/src/collection-source.vala"
	g_return_val_if_fail (filename != NULL, NULL);
#line 116 "/extra-data/checkout/gnome/gnome-boxes/src/collection-source.vala"
	self = (BoxesCollectionSource*) g_object_new (object_type, NULL);
#line 117 "/extra-data/checkout/gnome/gnome-boxes/src/collection-source.vala"
	_tmp0_ = filename;
#line 117 "/extra-data/checkout/gnome/gnome-boxes/src/collection-source.vala"
	boxes_iconfig_set_filename ((BoxesIConfig*) self, _tmp0_);
#line 118 "/extra-data/checkout/gnome/gnome-boxes/src/collection-source.vala"
	boxes_iconfig_set_has_file ((BoxesIConfig*) self, TRUE);
#line 119 "/extra-data/checkout/gnome/gnome-boxes/src/collection-source.vala"
	boxes_iconfig_load ((BoxesIConfig*) self, &_inner_error_);
#line 119 "/extra-data/checkout/gnome/gnome-boxes/src/collection-source.vala"
	if (_inner_error_ != NULL) {
#line 119 "/extra-data/checkout/gnome/gnome-boxes/src/collection-source.vala"
		g_propagate_error (error, _inner_error_);
#line 119 "/extra-data/checkout/gnome/gnome-boxes/src/collection-source.vala"
		_g_object_unref0 (self);
#line 119 "/extra-data/checkout/gnome/gnome-boxes/src/collection-source.vala"
		return NULL;
#line 762 "collection-source.c"
	}
#line 116 "/extra-data/checkout/gnome/gnome-boxes/src/collection-source.vala"
	return self;
#line 766 "collection-source.c"
}
