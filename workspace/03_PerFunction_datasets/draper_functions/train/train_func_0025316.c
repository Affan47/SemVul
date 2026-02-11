write_n (ACE_HANDLE handle,
                 const void *buf,
                 size_t len,
                 size_t *bt)
{
  size_t temp;
  size_t &bytes_transferred = bt == 0 ? temp : *bt;
  ssize_t n;

  for (bytes_transferred = 0;
       bytes_transferred < len;
       bytes_transferred += n)
    {
      n = ACE_OS::write (handle,
                         (char *) buf + bytes_transferred,
                         len - bytes_transferred);

      if (n == -1 || n == 0)
        {
          return n;
        }
    }

  return ACE_Utils::truncate_cast<ssize_t> (bytes_transferred);
}
