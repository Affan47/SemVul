clr_flags (ACE_HANDLE handle, int flags)
{
  ACE_TRACE ("ACE::clr_flags");

#if defined (ACE_LACKS_FCNTL)
  switch (flags)
    {
    case ACE_NONBLOCK:


      {
        int nonblock = 0;
        return ACE_OS::ioctl (handle, FIONBIO, &nonblock);
      }
    default:
      ACE_NOTSUP_RETURN (-1);
    }
#else
  int val = ACE_OS::fcntl (handle, F_GETFL, 0);

  if (val == -1)
    return -1;


  ACE_CLR_BITS (val, flags);

  if (ACE_OS::fcntl (handle, F_SETFL, val) == -1)
    return -1;
  else
    return 0;
#endif
}
