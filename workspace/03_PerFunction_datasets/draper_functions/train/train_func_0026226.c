tracker_namespace_get_prefix (TrackerNamespace *namespace)
{
	TrackerNamespacePrivate *priv;

	g_return_val_if_fail (TRACKER_IS_NAMESPACE (namespace), NULL);

	priv = GET_PRIV (namespace);

	if (!priv->prefix && priv->use_gvdb) {
		priv->prefix = g_strdup (tracker_ontologies_get_namespace_string_gvdb (priv->uri, "prefix"));
	}

	return priv->prefix;
}
