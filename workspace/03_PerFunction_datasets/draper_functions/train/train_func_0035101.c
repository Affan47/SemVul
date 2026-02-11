midgard_blob_read_content(MidgardBlob *self, gsize *bytes_read)
{
	g_assert(self != NULL);

	MidgardConnection *mgd = self->priv->mgd;
	MIDGARD_ERRNO_SET(mgd, MGD_ERR_OK);
	*bytes_read = 0;

	__get_filepath(self);

	if(!self->priv->filepath) {
		 midgard_set_error(mgd,
				 MGD_GENERIC_ERROR,
				 MGD_ERR_USER_DATA,
				 "Invalid attachment. "
				 "Can not read file from empty location");
		 return NULL;
	}

	gchar *content = NULL;
	GError *err = NULL;

	if (!g_file_get_contents(self->priv->filepath, &content, bytes_read, &err)) {
		midgard_set_error(self->priv->mgd, MGD_GENERIC_ERROR, MGD_ERR_INTERNAL,
				" %s ",	err&& err->message ? err->message : "Unknown reason");
		if (err)
			g_clear_error(&err);
		return NULL;
	}

	return content;
}
