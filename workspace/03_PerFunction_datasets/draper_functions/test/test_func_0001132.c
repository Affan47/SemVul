SelectSocket(int socketdescriptor, unsigned long msec)
{
#ifndef VTK_SOCKET_FAKE_API
  if (socketdescriptor < 0 )
    {
    vtkErrorMacro("Invalid descriptor.");
    return -1;
    }

  fd_set rset;
  int res;
  do
    {
    struct timeval tval;
    struct timeval* tvalptr = 0;
    if (msec>0)
      {
      tval.tv_sec = msec / 1000;
      tval.tv_usec = (msec % 1000)*1000;
      tvalptr = &tval;
      }

    FD_ZERO(&rset);
    FD_SET(socketdescriptor, &rset);


    res = select(socketdescriptor+1, &rset, 0, 0, tvalptr);
    }
  while ((res == vtkSocketErrorReturnMacro)
    && (vtkErrnoMacro == vtkSocketErrorIdMacro(EINTR)));

  if (res == 0)
    {

    return 0;
    }
  else
  if (res == vtkSocketErrorReturnMacro)
    {

    vtkSocketErrorMacro(vtkErrnoMacro, "Socket error in call to select.");
    return -1;
    }
  else
  if (!FD_ISSET(socketdescriptor, &rset))
     {
     vtkErrorMacro("Socket error in select. Descriptor not selected.");
     return -1;
     }


  return 1;
#else
  static_cast<void>(socketdescriptor);
  static_cast<void>(msec);
  return -1;
#endif
}
