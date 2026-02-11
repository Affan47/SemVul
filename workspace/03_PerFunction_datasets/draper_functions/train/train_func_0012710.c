handle_timed_open (ACE_Time_Value *timeout,
                        const ACE_TCHAR *name,
                        int flags,
                        int perms,
                        LPSECURITY_ATTRIBUTES sa)
{
  ACE_TRACE ("ACE::handle_timed_open");

  if (timeout != 0)
    {
#if !defined (ACE_WIN32)


      flags |= ACE_NONBLOCK;
#endif


      ACE_HANDLE const handle = ACE_OS::open (name, flags, perms, sa);

      if (handle == ACE_INVALID_HANDLE
          && (errno == EWOULDBLOCK
              && (timeout->sec () > 0 || timeout->usec () > 0)))

        errno = ETIMEDOUT;

      return handle;
    }
  else
    return ACE_OS::open (name, flags, perms, sa);
}
