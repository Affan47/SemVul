sourceview_io_new (Sourceview* sv)
{
	SourceviewIO* sio;

	g_return_val_if_fail (ANJUTA_IS_SOURCEVIEW(sv), NULL);

	sio = SOURCEVIEW_IO(g_object_new (SOURCEVIEW_TYPE_IO, NULL));

	sio->sv = sv;
	g_object_weak_ref (G_OBJECT (sv), on_sourceview_finalized, sio);


	sio->shell = ANJUTA_PLUGIN (sv->priv->plugin)->shell;
	g_object_add_weak_pointer (G_OBJECT (sio->shell), (gpointer*)&sio->shell);

	return sio;
}
