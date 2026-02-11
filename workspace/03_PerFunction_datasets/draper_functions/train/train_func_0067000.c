nm_secret_agent_has_permission (NMSecretAgent *agent, const char *permission)
{
	NMSecretAgentPrivate *priv;
	GSList *iter;

	g_return_val_if_fail (agent != NULL, FALSE);
	g_return_val_if_fail (permission != NULL, FALSE);

	priv = NM_SECRET_AGENT_GET_PRIVATE (agent);


	for (iter = priv->permissions; iter; iter = g_slist_next (iter)) {
		if (g_strcmp0 (permission, iter->data) == 0)
			return TRUE;
	}
	return FALSE;
}
