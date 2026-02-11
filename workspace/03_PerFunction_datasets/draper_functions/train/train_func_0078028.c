__get_filepath(MidgardBlob *self)
{
	if(self->priv->filepath)
		return;

	gchar *fname = NULL;
	gchar *location = NULL;
	gchar *up_a, *up_b;
	MidgardObject *attachment = self->priv->attachment;

	GParamSpec *pspec =
		g_object_class_find_property(
				G_OBJECT_GET_CLASS(G_OBJECT(attachment)), "location");


	if(!pspec){
		midgard_set_error(self->priv->mgd,
				MGD_GENERIC_ERROR,
				MGD_ERR_USER_DATA,
				"Invalid Object. "
				"Blobs can not be attached to %s",
				G_OBJECT_TYPE_NAME(G_OBJECT(attachment)));
		return;
	}

	g_object_get(G_OBJECT(self->priv->attachment), "location", &location, NULL);

	if(location == NULL || *location == '\0') {

		fname = midgard_uuid_new();
		up_a = g_strdup(" ");
		up_a[0] = g_ascii_toupper(fname[0]);
		up_b = g_strdup(" ");
		up_b[0] = g_ascii_toupper(fname[1]);

		location = g_build_path(G_DIR_SEPARATOR_S,
				up_a, up_b, fname, NULL);

		g_free(fname);
		g_free(up_a);
		g_free(up_b);

		g_object_set(G_OBJECT(self->priv->attachment), "location", location , NULL);

	}

	self->priv->location = location;

	self->priv->filepath =
		g_build_path(G_DIR_SEPARATOR_S,
				self->priv->blobdir, self->priv->location, NULL);
}
