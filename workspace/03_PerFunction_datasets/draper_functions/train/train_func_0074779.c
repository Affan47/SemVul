gen_tempname_len (char *tmpl, int suffixlen, int flags, int kind,
                  size_t x_suffix_len)
{
  size_t len;
  char *XXXXXX;
  unsigned int count;
  int fd = -1;
  int save_errno = errno;
  struct_stat64 st;
  struct randint_source *rand_src;


#define ATTEMPTS_MIN (62 * 62 * 62)


#if ATTEMPTS_MIN < TMP_MAX
  unsigned int attempts = TMP_MAX;
#else
  unsigned int attempts = ATTEMPTS_MIN;
#endif

  len = strlen (tmpl);
  if (len < x_suffix_len + suffixlen
      || ! check_x_suffix (&tmpl[len - x_suffix_len - suffixlen],
                           x_suffix_len))
    {
      __set_errno (EINVAL);
      return -1;
    }


  XXXXXX = &tmpl[len - x_suffix_len - suffixlen];


  rand_src = randint_all_new (NULL, x_suffix_len);
  if (! rand_src)
    return -1;

  for (count = 0; count < attempts; ++count)
    {
      size_t i;

      for (i = 0; i < x_suffix_len; i++)
        XXXXXX[i] = letters[randint_genmax (rand_src, sizeof letters - 2)];

      switch (kind)
        {
        case __GT_FILE:
          fd = __open (tmpl,
                       (flags & ~O_ACCMODE)
                       | O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
          break;

        case __GT_DIR:
          fd = __mkdir (tmpl, S_IRUSR | S_IWUSR | S_IXUSR);
          break;

        case __GT_NOCREATE:


          if (__lxstat64 (_STAT_VER, tmpl, &st) < 0)
            {
              if (errno == ENOENT)
                {
                  __set_errno (save_errno);
                  fd = 0;
                  goto done;
                }
              else
                {

                  fd = -1;
                  goto done;
                }
            }
          continue;

        default:
          assert (! "invalid KIND in __gen_tempname");
          abort ();
        }

      if (fd >= 0)
        {
          __set_errno (save_errno);
          goto done;
        }
      else if (errno != EEXIST)
        {
          fd = -1;
          goto done;
        }
    }

  randint_all_free (rand_src);


  __set_errno (EEXIST);
  return -1;

 done:
  {
    int saved_errno = errno;
    randint_all_free (rand_src);
    __set_errno (saved_errno);
  }
  return fd;
}
