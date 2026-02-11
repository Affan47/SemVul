uv_udp_set_ttl(uv_udp_t* handle, int ttl) {
  if (ttl < 1 || ttl > 255)
    return -EINVAL;

  if (setsockopt(handle->io_watcher.fd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)))
    return -errno;

  return 0;
}
