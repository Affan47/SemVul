uv__tcp_keepalive(uv_tcp_t* handle, int enable, unsigned int delay) {
  if (setsockopt(handle->fd,
                 SOL_SOCKET,
                 SO_KEEPALIVE,
                 &enable,
                 sizeof enable) == -1) {
    uv__set_sys_error(handle->loop, errno);
    return -1;
  }

#ifdef TCP_KEEPIDLE
  if (enable && setsockopt(handle->fd,
                           IPPROTO_TCP,
                           TCP_KEEPIDLE,
                           &delay,
                           sizeof delay) == -1) {
    uv__set_sys_error(handle->loop, errno);
    return -1;
  }
#endif

#ifdef TCP_KEEPALIVE
  if (enable && setsockopt(handle->fd,
                           IPPROTO_TCP,
                           TCP_KEEPALIVE,
                           &delay,
                           sizeof delay) == -1) {
    uv__set_sys_error(handle->loop, errno);
    return -1;
  }
#endif

  return 0;
}
