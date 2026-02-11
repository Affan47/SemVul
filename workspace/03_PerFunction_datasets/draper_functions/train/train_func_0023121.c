ssh_forward_cancel(ssh_session session, const char *address, int port) {
  ssh_buffer buffer = NULL;
  ssh_string addr = NULL;
  int rc = SSH_ERROR;

  if(session->global_req_state != SSH_CHANNEL_REQ_STATE_NONE)
    goto pending;

  buffer = ssh_buffer_new();
  if (buffer == NULL) {
    ssh_set_error_oom(session);
    goto error;
  }

  addr = ssh_string_from_char(address ? address : "");
  if (addr == NULL) {
    ssh_set_error_oom(session);
    goto error;
  }

  if (buffer_add_ssh_string(buffer, addr) < 0 ||
      buffer_add_u32(buffer, htonl(port)) < 0) {
    ssh_set_error_oom(session);
    goto error;
  }
pending:
  rc = global_request(session, "cancel-tcpip-forward", buffer, 1);

error:
  ssh_buffer_free(buffer);
  ssh_string_free(addr);
  return rc;
}
