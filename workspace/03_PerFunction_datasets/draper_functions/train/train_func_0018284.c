th_set_mode(TAR *t, mode_t fmode)
{
#ifndef WIN32
#ifndef __BEOS__
  if (S_ISSOCK(fmode))
  {
    fmode &= ~S_IFSOCK;
    fmode |= S_IFIFO;
  }
#endif
#endif

  int_to_oct(fmode & 07777777, (t)->th_buf.mode, 8);
}
