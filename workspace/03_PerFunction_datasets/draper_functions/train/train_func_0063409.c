sftp_handle_alloc(sftp_session sftp, void *info) {
  ssh_string ret;
  uint32_t val;
  int i;

  if (sftp->handles == NULL) {
    sftp->handles = malloc(sizeof(void *) * SFTP_HANDLES);
    if (sftp->handles == NULL) {
      return NULL;
    }
    memset(sftp->handles, 0, sizeof(void *) * SFTP_HANDLES);
  }

  for (i = 0; i < SFTP_HANDLES; i++) {
    if (sftp->handles[i] == NULL) {
      break;
    }
  }

  if (i == SFTP_HANDLES) {
    return NULL;
  }

  val = i;
  ret = ssh_string_new(4);
  if (ret == NULL) {
    return NULL;
  }

  memcpy(ssh_string_data(ret), &val, sizeof(uint32_t));
  sftp->handles[i] = info;

  return ret;
}
