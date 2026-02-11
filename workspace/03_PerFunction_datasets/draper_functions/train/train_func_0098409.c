uv_tcp_connect(uv_connect_t* req,
                   uv_tcp_t* handle,
                   struct sockaddr_in address,
                   uv_connect_cb cb) {
  if (handle->type != UV_TCP || address.sin_family != AF_INET)
    return UV_EINVAL;
  else
    return uv__tcp_connect(req, handle, address, cb);
}
