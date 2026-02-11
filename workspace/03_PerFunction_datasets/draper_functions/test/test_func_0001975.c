gmpc_metaimage_clear_entry (GmpcMetaImage * self)
{
#line 1562 "gmpc-metaimage.c"
#define __GOB_FUNCTION__ "Gmpc:MetaImage::clear_entry"
#line 766 "gmpc-metaimage.gob"
	g_return_if_fail (self != NULL);
#line 766 "gmpc-metaimage.gob"
	g_return_if_fail (GMPC_IS_METAIMAGE (self));
#line 1568 "gmpc-metaimage.c"
{
#line 769 "gmpc-metaimage.gob"

        MetaData *met = meta_data_new();
        met->content_type = META_DATA_CONTENT_EMPTY;
        met->plugin_name = "User set";
        met->type = self->image_type;
		meta_data_set_cache(self->_priv->song, META_DATA_UNAVAILABLE, met);
		gmpc_meta_watcher_data_changed(gmw, self->_priv->song, self->image_type, META_DATA_UNAVAILABLE, NULL);
        meta_data_free(met);
	}}
