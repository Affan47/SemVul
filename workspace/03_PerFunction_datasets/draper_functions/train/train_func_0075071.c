uv__after_work(eio_req *eio) {
  uv_work_t* req = eio->data;
  uv_unref(req->loop);
  if (req->after_work_cb) {
    req->after_work_cb(req);
  }
  return 0;
}
