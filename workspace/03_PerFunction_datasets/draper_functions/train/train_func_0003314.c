unix_ipc_sendmsg(struct unix_client *client,
					const bt_audio_msg_header_t *msg)
{
	const char *type = bt_audio_strtype(msg->type);
	const char *name = bt_audio_strname(msg->name);

	DBG("Audio API: %s -> %s", type, name);

	if (send(client->sock, msg, msg->length, 0) < 0)
		error("Error %s(%d)", strerror(errno), errno);
}
