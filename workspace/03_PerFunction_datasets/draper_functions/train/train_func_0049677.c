ssh_channel_send_eof(ssh_channel channel){
  ssh_session session;
  int rc = SSH_ERROR;

  if(channel == NULL) {
      return rc;
  }

  session = channel->session;

  if (buffer_add_u8(session->out_buffer, SSH2_MSG_CHANNEL_EOF) < 0) {
    ssh_set_error_oom(session);
    goto error;
  }
  if (buffer_add_u32(session->out_buffer,htonl(channel->remote_channel)) < 0) {
    ssh_set_error_oom(session);
    goto error;
  }
  rc = packet_send(session);
  SSH_LOG(SSH_LOG_PACKET,
      "Sent a EOF on client channel (%d:%d)",
      channel->local_channel,
      channel->remote_channel);

  rc = ssh_channel_flush(channel);
  if(rc == SSH_ERROR)
    goto error;

  channel->local_eof = 1;

  return rc;
error:
  ssh_buffer_reinit(session->out_buffer);

  return rc;
}
