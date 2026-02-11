async (bool set) const


{
  int arg = set;
  if (::ioctl (rep->sock, FIOASYNC, &arg) == -1)
    throw sockerr (errno, "sockbuf::async", sockname.text.c_str());
}
