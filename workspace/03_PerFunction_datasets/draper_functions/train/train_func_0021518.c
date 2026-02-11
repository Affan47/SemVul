ssh_packet_parse_type(ssh_session session) {
  memset(&session->in_packet, 0, sizeof(PACKET));
  if(session->in_buffer == NULL) {
    return SSH_ERROR;
  }

  if(buffer_get_u8(session->in_buffer, &session->in_packet.type) == 0) {
    ssh_set_error(session, SSH_FATAL, "Packet too short to read type");
    return SSH_ERROR;
  }

  session->in_packet.valid = 1;

  return SSH_OK;
}
