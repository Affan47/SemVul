send_n_i (ACE_HANDLE handle,
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

      n = ACE::send_i (handle,
                       (char *) buf + bytes_transferred,
                       len - bytes_transferred);

      if (n == 0)
        {
          return 0;
        }


      if (n == -1)
        {

          if (errno == EWOULDBLOCK || errno == ENOBUFS)
            {

              int const result = ACE::handle_write_ready (handle, 0);


              if (result != -1)
                {

                  n = 0;
                  continue;
                }
            }


          return -1;
        }
    }

  return ACE_Utils::truncate_cast<ssize_t> (bytes_transferred);
}
