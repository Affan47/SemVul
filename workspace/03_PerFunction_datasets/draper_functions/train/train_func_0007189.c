ssh_channel_request_env(ssh_channel channel, const char *name, const char *value) {
  ssh_buffer buffer = NULL;
  ssh_string str = NULL;
  int rc = SSH_ERROR;

  if(channel == NULL) {
      return SSH_ERROR;
  }
  if(name == NULL || value == NULL) {
      ssh_set_error_invalid(channel->session);
      return rc;
  }
  switch(channel->request_state){
  case SSH_CHANNEL_REQ_STATE_NONE:
    break;
  default:
    goto pending;
  }
  buffer = ssh_buffer_new();
  if (buffer == NULL) {
    ssh_set_error_oom(channel->session);
    goto error;
  }

  str = ssh_string_from_char(name);
  if (str == NULL) {
    ssh_set_error_oom(channel->session);
    goto error;
  }

  if (buffer_add_ssh_string(buffer, str) < 0) {
    ssh_set_error_oom(channel->session);
    goto error;
  }

  ssh_string_free(str);
  str = ssh_string_from_char(value);
  if (str == NULL) {
    ssh_set_error_oom(channel->session);
    goto error;
  }

  if (buffer_add_ssh_string(buffer, str) < 0) {
    ssh_set_error_oom(channel->session);
    goto error;
  }
pending:
  rc = channel_request(channel, "env", buffer,1);
error:
  ssh_buffer_free(buffer);
  ssh_string_free(str);

  return rc;
}
