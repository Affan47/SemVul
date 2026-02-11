sftp_parse_string(struct sftpjob *job, char **strp, size_t *lenp) {
  uint32_t len, rc;
  char *str;

  if((rc = sftp_parse_uint32(job, &len)) != SSH_FX_OK)
    return rc;
  if(!(len + 1))
    return SSH_FX_BAD_MESSAGE;
  if(job->left < len)
    return SSH_FX_BAD_MESSAGE;
  if(lenp)
    *lenp = len;
  if(strp) {
    str = sftp_alloc(job->a, len + 1);
    memcpy(str, job->ptr, len);
    *strp = str;
  }
  job->ptr += len;
  job->left -= len;
  return SSH_FX_OK;
}
