recvfrom (ACE_HANDLE handle,
               char *buf,
               int len,
               int flags,
               struct sockaddr *addr,
               int *addrlen,
               const ACE_Time_Value *timeout)
{
  if (timeout == 0)
    return ACE_OS::recvfrom (handle, buf, len, flags, addr, addrlen);
  else
    {
      int val = 0;
      if (ACE::enter_recv_timedwait (handle, timeout, val) == -1)
        return -1;
      else
        {
          ssize_t bytes_transferred =
            ACE_OS::recvfrom (handle, buf, len, flags, addr, addrlen);
          ACE::restore_non_blocking_mode (handle, val);
          return bytes_transferred;
        }
    }
}
