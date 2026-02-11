eio_write (int fd, void *buf, size_t length, off_t offset, int pri, eio_cb cb, void *data)
{
  REQ (EIO_WRITE); req->int1 = fd; req->offs = offset; req->size = length; req->ptr2 = buf; SEND;
}
