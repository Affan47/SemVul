link_exists_p (int dfd, const char *dir, size_t dirlen, const char *fname,
               glob_t *pglob, int flags)
{
# if defined _LIBC || HAVE_FSTATAT
  if (__builtin_expect (flags & GLOB_ALTDIRFUNC, 0))
    return link_exists2_p (dir, dirlen, fname, pglob);
  else
    {


      struct_stat64 st64;
      return __fxstatat64 (_STAT_VER, dfd, fname, &st64, 0) == 0;
    }
# else
  return link_exists2_p (dir, dirlen, fname, pglob, flags);
# endif
}
