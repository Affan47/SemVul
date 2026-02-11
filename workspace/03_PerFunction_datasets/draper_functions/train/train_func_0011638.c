soup_socket_disconnect (SoupSocket *sock)
{
	SoupSocketPrivate *priv;
	gboolean already_disconnected = FALSE;

	g_return_if_fail (SOUP_IS_SOCKET (sock));
	priv = SOUP_SOCKET_GET_PRIVATE (sock);

	if (priv->connect_cancel) {
		disconnect_internal (sock, FALSE);
		g_cancellable_cancel (priv->connect_cancel);
		return;
	} else if (g_mutex_trylock (&priv->iolock)) {
		if (priv->gsock)
			disconnect_internal (sock, TRUE);
		else
			already_disconnected = TRUE;
		g_mutex_unlock (&priv->iolock);
	} else {


		g_socket_shutdown (priv->gsock, TRUE, TRUE, NULL);
	}

	if (already_disconnected)
		return;


	g_object_ref (sock);

	if (priv->non_blocking) {

		g_signal_emit (sock, signals[READABLE], 0);
	}


	g_signal_emit (sock, signals[DISCONNECTED], 0);

	g_object_unref (sock);
}
