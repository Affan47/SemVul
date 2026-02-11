closeonexec (bool set) const


{
#if !defined( __sgi) && !defined(__hpux)
  if (set) {
    if (::ioctl (rep->sock, FIOCLEX, 0) == -1)
      throw sockerr (errno, "sockbuf::closeonexec", sockname.text.c_str());
  } else {
    if (::ioctl (rep->sock, FIONCLEX, 0) == -1)
      throw sockerr (errno, "sockbuf::closeonexec", sockname.text.c_str());
  }
#endif
}
