ssh_message_channel_request_open_reply_accept_channel(ssh_message msg, ssh_channel chan) {
    ssh_session session;
    int rc;

    if (msg == NULL) {
        return SSH_ERROR;
    }

    session = msg->session;

    chan->local_channel = ssh_channel_new_id(session);
    chan->local_maxpacket = 35000;
    chan->local_window = 32000;
    chan->remote_channel = msg->channel_request_open.sender;
    chan->remote_maxpacket = msg->channel_request_open.packet_size;
    chan->remote_window = msg->channel_request_open.window;
    chan->state = SSH_CHANNEL_STATE_OPEN;

    rc = buffer_add_u8(session->out_buffer, SSH2_MSG_CHANNEL_OPEN_CONFIRMATION);
    if (rc < 0) {
        return SSH_ERROR;
    }

    rc = buffer_add_u32(session->out_buffer, htonl(chan->remote_channel));
    if (rc < 0) {
        return SSH_ERROR;
    }

    rc =buffer_add_u32(session->out_buffer, htonl(chan->local_channel));
    if (rc < 0) {
        return SSH_ERROR;
    }

    rc = buffer_add_u32(session->out_buffer, htonl(chan->local_window));
    if (rc < 0) {
        return SSH_ERROR;
    }

    rc = buffer_add_u32(session->out_buffer, htonl(chan->local_maxpacket));
    if (rc < 0) {
        return SSH_ERROR;
    }

    SSH_LOG(SSH_LOG_PACKET,
            "Accepting a channel request_open for chan %d",
            chan->remote_channel);

    rc = packet_send(session);

    return rc;
}
