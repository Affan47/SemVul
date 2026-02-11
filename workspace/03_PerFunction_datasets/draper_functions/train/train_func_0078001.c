otp_connect(const char *path)
{
  int fd;
  struct sockaddr_un sa;
  size_t sp_len;


  sp_len = strlen(path);
  if (sp_len > sizeof(sa.sun_path) - 1) {
    (void) radlog(L_ERR, "rlm_otp: %s: rendezvous point name too long",
                  __func__);
    return -1;
  }
  sa.sun_family = AF_UNIX;
  (void) strcpy(sa.sun_path, path);


  if ((fd = socket(PF_UNIX, SOCK_STREAM, 0)) == -1) {
    (void) radlog(L_ERR, "rlm_otp: %s: socket: %s", __func__, strerror(errno));
    return -1;
  }
  if (connect(fd, (struct sockaddr *) &sa,
              sizeof(sa.sun_family) + sp_len) == -1) {
    (void) radlog(L_ERR, "rlm_otp: %s: connect(%s): %s",
                  __func__, path, strerror(errno));
    (void) close(fd);
    return -1;
  }
  return fd;
}
