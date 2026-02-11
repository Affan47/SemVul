evpipe_write (EV_P_ EV_ATOMIC_T *flag)
{
  if (!*flag)
    {
      int old_errno = errno;
      char dummy;

      *flag = 1;

#if EV_USE_EVENTFD
      if (evfd >= 0)
        {
          uint64_t counter = 1;
          write (evfd, &counter, sizeof (uint64_t));
        }
      else
#endif


        write (evpipe [1], &dummy, 1);

      errno = old_errno;
    }
}
