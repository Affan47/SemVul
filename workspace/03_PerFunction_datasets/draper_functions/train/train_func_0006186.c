server_side_source_set_server (EServerSideSource *source,
                               ESourceRegistryServer *server)
{
	g_return_if_fail (E_IS_SOURCE_REGISTRY_SERVER (server));
	g_return_if_fail (source->priv->server == NULL);

	source->priv->server = server;

	g_object_add_weak_pointer (
		G_OBJECT (server), &source->priv->server);
}
