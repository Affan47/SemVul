ssh2_msg_channel_failure(Ssh ssh, struct Packet *pktin)
{


    struct ssh_channel *c;

    c = ssh2_channel_msg(ssh, pktin);
    if (!c)
	return;
    if (!ssh2_handle_winadj_response(c))
	ssh_disconnect(ssh, NULL,
		       "Received unsolicited SSH_MSG_CHANNEL_FAILURE",
		       SSH2_DISCONNECT_PROTOCOL_ERROR, FALSE);
}
