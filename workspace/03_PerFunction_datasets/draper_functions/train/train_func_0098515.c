eio_grp (eio_cb cb, void *data)
{
  const int pri = EIO_PRI_MAX;

  REQ (EIO_GROUP); SEND;
}
