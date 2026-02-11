request_secrets (GetSecretsInfo *info)
{
	g_return_if_fail (info != NULL);

	nm_remote_connection_get_secrets (NM_REMOTE_CONNECTION (info->self->orig_connection),
	                                  info->setting_name,
	                                  get_secrets_cb,
	                                  info);
}
