aim_chat_getname(aim_conn_t *conn)
{
	struct chatconnpriv *ccp;

	if (!conn)
		return NULL;

	if (conn->type != AIM_CONN_TYPE_CHAT)
		return NULL;

	ccp = (struct chatconnpriv *)conn->priv;

	return ccp->name;
}
