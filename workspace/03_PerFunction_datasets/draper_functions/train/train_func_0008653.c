uv_tcp_getpeername(uv_tcp_t* handle, struct sockaddr* name,
    int* namelen) {
  socklen_t socklen;
  int saved_errno;
  int rv = 0;


  saved_errno = errno;

  if (handle->delayed_error) {
    uv__set_sys_error(handle->loop, handle->delayed_error);
    rv = -1;
    goto out;
  }

  if (uv__stream_fd(handle) < 0) {
    uv__set_sys_error(handle->loop, EINVAL);
    rv = -1;
    goto out;
  }


  socklen = (socklen_t)*namelen;

  if (getpeername(uv__stream_fd(handle), name, &socklen) == -1) {
    uv__set_sys_error(handle->loop, errno);
    rv = -1;
  } else {
    *namelen = (int)socklen;
  }

out:
  errno = saved_errno;
  return rv;
}
