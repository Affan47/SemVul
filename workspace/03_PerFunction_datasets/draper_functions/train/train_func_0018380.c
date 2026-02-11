__lio_listio_item_notify (int mode, struct aiocb *const list[], int nent,
			  struct sigevent *sig)
{

  if (mode != LIO_WAIT && mode != LIO_NOWAIT)
    {
      __set_errno (EINVAL);
      return -1;
    }

  return lio_listio_internal (mode, list, nent, sig);
}
