acl_set_ip_sec(struct iscsi_acl *client, int ip_sec)
{
	if (!client || client->signature != ACL_SIGNATURE)
		return AUTH_STATUS_ERROR;

	if (client->phase != AUTH_PHASE_CONFIGURE) {
		client->phase = AUTH_PHASE_ERROR;
		return AUTH_STATUS_ERROR;
	}

	client->ip_sec = ip_sec;

	return AUTH_STATUS_NO_ERROR;
}
