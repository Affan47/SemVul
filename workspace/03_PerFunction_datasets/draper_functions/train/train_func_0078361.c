fchmodat (fd, file, mode, flag)
     int fd;
     const char *file;
     mode_t mode;
     int flag;
{
  if (flag & ~AT_SYMLINK_NOFOLLOW)
    {
      __set_errno (EINVAL);
      return -1;
    }
#ifndef __NR_lchmod
  if (flag & AT_SYMLINK_NOFOLLOW)
    {
      __set_errno (ENOTSUP);
      return -1;
    }
#endif

  int result;

#ifdef __NR_fchmodat
# ifndef __ASSUME_ATFCTS
  if (__have_atfcts >= 0)
# endif
    {
      result = INLINE_SYSCALL (fchmodat, 3, fd, file, mode);
# ifndef __ASSUME_ATFCTS
      if (result == -1 && errno == ENOSYS)
	__have_atfcts = -1;
      else
# endif
	return result;
    }
#endif

#ifndef __ASSUME_ATFCTS
  char *buf = NULL;

  if (fd != AT_FDCWD && file[0] != '/')
    {
      size_t filelen = strlen (file);
      if (__builtin_expect (filelen == 0, 0))
	{
	  __set_errno (ENOENT);
	  return -1;
	}

      static const char procfd[] = "/proc/self/fd/%d/%s";


      size_t buflen = sizeof (procfd) + sizeof (int) * 3 + filelen;
      buf = alloca (buflen);

      __snprintf (buf, buflen, procfd, fd, file);
      file = buf;
    }

  INTERNAL_SYSCALL_DECL (err);

# ifdef __NR_lchmod
  if (flag & AT_SYMLINK_NOFOLLOW)
    result = INTERNAL_SYSCALL (lchmod, err, 2, file, mode);
  else
# endif
    result = INTERNAL_SYSCALL (chmod, err, 2, file, mode);

  if (__builtin_expect (INTERNAL_SYSCALL_ERROR_P (result, err), 0))
    {
      __atfct_seterrno (INTERNAL_SYSCALL_ERRNO (result, err), fd, buf);
      result = -1;
    }

  return result;
#endif
}
