e_client_retrieve_capabilities_sync (EClient *client,
                                     gchar **capabilities,
                                     GCancellable *cancellable,
                                     GError **error)
{
	EClientClass *class;
	gboolean res = FALSE;

	g_return_val_if_fail (E_IS_CLIENT (client), FALSE);
	g_return_val_if_fail (capabilities != NULL, FALSE);

	class = E_CLIENT_GET_CLASS (client);
	g_return_val_if_fail (class != NULL, FALSE);
	g_return_val_if_fail (class->retrieve_capabilities_sync != NULL, FALSE);

	*capabilities = NULL;
	res = class->retrieve_capabilities_sync (
		client, capabilities, cancellable, error);

	e_client_set_capabilities (client, res ? *capabilities : NULL);

	return res;
}
