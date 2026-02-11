soup_message_set_http_version (SoupMessage *msg, SoupHTTPVersion version)
{
	SoupMessagePrivate *priv;

	g_return_if_fail (SOUP_IS_MESSAGE (msg));
	priv = SOUP_MESSAGE_GET_PRIVATE (msg);

	priv->http_version = version;
	if (msg->status_code == SOUP_STATUS_NONE)
		priv->orig_http_version = version;
	g_object_notify (G_OBJECT (msg), SOUP_MESSAGE_HTTP_VERSION);
}
