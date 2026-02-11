eio_custom (eio_cb execute, int pri, eio_cb cb, void *data)
{
  REQ (EIO_CUSTOM); req->feed = (void (*)(eio_req *))execute; SEND;
}
