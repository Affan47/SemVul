nm_secret_agent_delete_secrets (NMSecretAgent *self,
                                NMConnection *connection,
                                NMSecretAgentCallback callback,
                                gpointer callback_data)
{
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (connection != NULL, NULL);


	return agent_new_save_delete (self,
	                              connection,
	                              NM_SETTING_HASH_FLAG_NO_SECRETS,
	                              "DeleteSecrets",
	                              callback,
	                              callback_data);
}
