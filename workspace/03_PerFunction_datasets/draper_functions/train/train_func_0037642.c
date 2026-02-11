uv__udp_send(uv_udp_send_t* req,
                        uv_udp_t* handle,
                        uv_buf_t bufs[],
                        int bufcnt,
                        struct sockaddr* addr,
                        socklen_t addrlen,
                        uv_udp_send_cb send_cb) {
  if (uv__udp_maybe_deferred_bind(handle, addr->sa_family))
    return -1;


  handle->loop->counters.req_init++;

  memcpy(&req->addr, addr, addrlen);
  req->addrlen = addrlen;
  req->send_cb = send_cb;
  req->handle = handle;
  req->bufcnt = bufcnt;
  req->type = UV_UDP_SEND;

  if (bufcnt <= UV_REQ_BUFSML_SIZE) {
    req->bufs = req->bufsml;
  }
  else if ((req->bufs = malloc(bufcnt * sizeof(bufs[0]))) == NULL) {
    uv__set_sys_error(handle->loop, ENOMEM);
    return -1;
  }
  memcpy(req->bufs, bufs, bufcnt * sizeof(bufs[0]));

  ngx_queue_insert_tail(&handle->write_queue, &req->queue);
  uv__udp_watcher_start(handle, &handle->write_watcher);

  return 0;
}
