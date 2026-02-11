sshv2_get_file (gftp_request * request, const char *file, off_t startsize)
{
  int ret;

  if ((ret = sshv2_open_file (request, file, startsize, SSH_FXF_READ)) < 0)
    return (ret);

  return (sshv2_get_file_size (request, file));
}
