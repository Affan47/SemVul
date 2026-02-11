add_and_activate_auth_done (PendingActivation *pending, GError *error)
{
	if (error)
		pending_activation_destroy (pending, error, NULL);
	else {
		NMManagerPrivate *priv = NM_MANAGER_GET_PRIVATE (pending->manager);


		nm_settings_add_connection (priv->settings,
                                    pending->connection,
                                    pending->context,
                                    activation_add_done,
                                    pending);
	}
}
