uv_udp_getsockname(uv_udp_t* handle, struct sockaddr* name, int* namelen) {
  socklen_t socklen;

  if (handle->io_watcher.fd == -1)
    return -EINVAL;


  socklen = (socklen_t) *namelen;

  if (getsockname(handle->io_watcher.fd, name, &socklen))
    return -errno;

  *namelen = (int) socklen;
  return 0;
}
