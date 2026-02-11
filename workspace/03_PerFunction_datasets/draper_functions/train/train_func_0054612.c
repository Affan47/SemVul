Receive(void* data, int length, int readFully)
{
#ifndef VTK_SOCKET_FAKE_API
  if (!this->GetConnected())
    {
    vtkErrorMacro("Not connected.");
    return 0;
    }

#if defined(_WIN32) && !defined(__CYGWIN__)
  int trys = 0;
#endif

  char* buffer = reinterpret_cast<char*>(data);
  int total = 0;
  do
    {
    int nRecvd;
    vtkRestartInterruptedSystemCallMacro(
      recv(this->SocketDescriptor, buffer+total, length-total, 0),
      nRecvd);

    if (nRecvd == 0)
      {

      return 0;
      }

#if defined(_WIN32) && !defined(__CYGWIN__)
    if ((nRecvd == vtkSocketErrorReturnMacro)
      && (WSAGetLastError() == WSAENOBUFS))
      {


      if ((trys++ < 1000))
        {
        Sleep(1);
        continue;
        }
      vtkSocketErrorMacro(vtkErrnoMacro, "Socket error in call to recv.");
      return 0;
      }
#endif

    total += nRecvd;
    }
  while( readFully && (total < length));

  return total;
#else
  static_cast<void>(data);
  static_cast<void>(length);
  static_cast<void>(readFully);
  return 0;
#endif
}
