eio_chmod (const char *path, eio_mode_t mode, int pri, eio_cb cb, void *data)
{
  REQ (EIO_CHMOD); PATH; req->int2 = (long)mode; SEND;
}
