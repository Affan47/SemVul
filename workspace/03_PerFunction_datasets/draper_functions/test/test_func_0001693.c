brasero_disc_message_set_timeout (BraseroDiscMessage *self,
				  guint mseconds)
{
	BraseroDiscMessagePrivate *priv;

	priv = BRASERO_DISC_MESSAGE_PRIVATE (self);

	if (priv->timeout) {
		g_source_remove (priv->timeout);
		priv->timeout = 0;
	}

	if (mseconds > 0)
		priv->timeout = g_timeout_add (mseconds,
					       brasero_disc_message_timeout,
					       self);
}
