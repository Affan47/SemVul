dh_handshake_server(ssh_session session) {
  ssh_key privkey;

  ssh_string sig_blob;
  ssh_string f;

  if (dh_generate_y(session) < 0) {
    ssh_set_error(session, SSH_FATAL, "Could not create y number");
    return -1;
  }
  if (dh_generate_f(session) < 0) {
    ssh_set_error(session, SSH_FATAL, "Could not create f number");
    return -1;
  }

  f = dh_get_f(session);
  if (f == NULL) {
    ssh_set_error(session, SSH_FATAL, "Could not get the f number");
    return -1;
  }

  if (ssh_get_key_params(session,&privkey) != SSH_OK){
      ssh_string_free(f);
      return -1;
  }

  if (dh_build_k(session) < 0) {
    ssh_set_error(session, SSH_FATAL, "Could not import the public key");
    ssh_string_free(f);
    return -1;
  }

  if (make_sessionid(session) != SSH_OK) {
    ssh_set_error(session, SSH_FATAL, "Could not create a session id");
    ssh_string_free(f);
    return -1;
  }

  sig_blob = ssh_srv_pki_do_sign_sessionid(session, privkey);
  if (sig_blob == NULL) {
    ssh_set_error(session, SSH_FATAL, "Could not sign the session id");
    ssh_string_free(f);
    return -1;
  }

  if (buffer_add_u8(session->out_buffer, SSH2_MSG_KEXDH_REPLY) < 0 ||
      buffer_add_ssh_string(session->out_buffer,
              session->next_crypto->server_pubkey) < 0 ||
      buffer_add_ssh_string(session->out_buffer, f) < 0 ||
      buffer_add_ssh_string(session->out_buffer, sig_blob) < 0) {
    ssh_set_error(session, SSH_FATAL, "Not enough space");
    buffer_reinit(session->out_buffer);
    ssh_string_free(f);
    ssh_string_free(sig_blob);
    return -1;
  }
  ssh_string_free(f);
  ssh_string_free(sig_blob);
  if (packet_send(session) == SSH_ERROR) {
    return -1;
  }

  if (buffer_add_u8(session->out_buffer, SSH2_MSG_NEWKEYS) < 0) {
    buffer_reinit(session->out_buffer);
    return -1;
  }

  if (packet_send(session) == SSH_ERROR) {
    return -1;
  }
  SSH_LOG(SSH_LOG_PACKET, "SSH_MSG_NEWKEYS sent");
  session->dh_handshake_state=DH_STATE_NEWKEYS_SENT;

  return 0;
}
