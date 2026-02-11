shutdown (void)
{
  if ( handle != -1 )
  {
#if defined(UL_CYGWIN) || !defined (UL_WIN32)
    if (isStream)
    {
        errno = 0;
        if (::shutdown (handle, SHUT_RDWR) != 0)
        {
            printf ("netSocket::shutdown: %s on fd %u\n", strerror (errno),
                    handle);
        }
    }
#endif
    handle = -1 ;
  }
}
