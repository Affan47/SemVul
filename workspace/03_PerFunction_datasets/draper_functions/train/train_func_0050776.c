_nm_object_ensure_inited (NMObject *object)
{
	NMObjectPrivate *priv = NM_OBJECT_GET_PRIVATE (object);
	GError *error = NULL;

	if (!priv->inited) {
		if (!g_initable_init (G_INITABLE (object), NULL, &error)) {
			g_warning ("Could not initialize %s %s: %s",
			           G_OBJECT_TYPE_NAME (object), priv->path,
			           error->message);
			g_error_free (error);


			priv->inited = TRUE;
		}
	}
}
