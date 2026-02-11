_gnutls_writev_emu (gnutls_session_t session, const giovec_t * giovec,
                    int giovec_cnt)
{
  int ret = 0, j = 0;
  gnutls_transport_ptr_t fd = session->internals.transport_send_ptr;
  void *iptr;
  size_t sizeOfPtr;
  size_t total = 0;

  for (j = 0; j < giovec_cnt; j++)
    {
      sizeOfPtr = giovec[j].iov_len;
      iptr = giovec[j].iov_base;

      ret = session->internals.push_func (fd, iptr, sizeOfPtr);

      if (ret == -1)
        break;

      total += ret;

      if (ret != giovec[j].iov_len)
        break;
    }

  if (total > 0)
    return total;

  return ret;
}
