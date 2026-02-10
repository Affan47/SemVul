invalidate_cache (int fd, off_t len)
{
  int adv_ret = -1;


  off_t clen = cache_round (fd, len);
  if (len && !clen)
    return true;
  if (!len && !clen && max_records)
    return true;
  off_t pending = len ? cache_round (fd, 0) : 0;

  if (fd == STDIN_FILENO)
    {
      if (input_seekable)
        {


#if HAVE_POSIX_FADVISE
            adv_ret = posix_fadvise (fd, input_offset - clen - pending, clen,
                                     POSIX_FADV_DONTNEED);
#else
            errno = ENOTSUP;
#endif
        }
      else
        errno = ESPIPE;
    }
  else if (fd == STDOUT_FILENO)
    {
      static off_t output_offset = -2;

      if (output_offset != -1)
        {
          if (0 > output_offset)
            {
              output_offset = lseek (fd, 0, SEEK_CUR);
              output_offset -= clen + pending;
            }
          if (0 <= output_offset)
            {
#if HAVE_POSIX_FADVISE
              adv_ret = posix_fadvise (fd, output_offset, clen,
                                       POSIX_FADV_DONTNEED);
#else
              errno = ENOTSUP;
#endif
              output_offset += clen + pending;
            }
        }
    }

  return adv_ret != -1 ? true : false;
}
