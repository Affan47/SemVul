imapx_untagged_recent (CamelIMAPXServer *is,
                       CamelIMAPXStream *stream,
                       GCancellable *cancellable,
                       GError **error)
{
	g_return_val_if_fail (CAMEL_IS_IMAPX_SERVER (is), FALSE);

	c (is->tagprefix, "recent: %lu\n", is->priv->context->id);
	is->priv->recent = is->priv->context->id;

	return TRUE;
}
