midgard_blob_remove_file(MidgardBlob *self, GError **error)
{
	g_assert(self != NULL);

	MidgardConnection *mgd = self->priv->mgd;
	MIDGARD_ERRNO_SET(mgd, MGD_ERR_OK);

	__get_filepath(self);
	if(!self->priv->filepath) {
		MIDGARD_ERRNO_SET(self->priv->mgd, MGD_ERR_INTERNAL);
		g_set_error (error, MGD_GENERIC_ERROR, MGD_ERR_INTERNAL,
				"Can not delete '%s'. No file location", self->priv->filepath);
		return FALSE;
	}

	if(!midgard_blob_exists(self)) {
		MIDGARD_ERRNO_SET(self->priv->mgd, MGD_ERR_INTERNAL);
		g_set_error (error, MGD_GENERIC_ERROR, MGD_ERR_INTERNAL,
				"Can not delete '%s'. File doesn't exists", self->priv->filepath);
		return FALSE;
	}

	guint deleted = g_remove(self->priv->filepath);

	if(deleted == 0)
		return TRUE;

	g_set_error (error, MGD_GENERIC_ERROR, MGD_ERR_INTERNAL, "Can not delete '%s'. Unknown reason", self->priv->filepath);
	MIDGARD_ERRNO_SET(self->priv->mgd, MGD_ERR_INTERNAL);

	return FALSE;
}
