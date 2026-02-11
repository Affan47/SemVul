Send(const void* data, int length)
{
#ifndef VTK_SOCKET_FAKE_API
  if (!this->GetConnected())
    {
    vtkErrorMacro("Not connected.");
    return 0;
    }
  if (length == 0)
    {

    return 1;
    }
  const char* buffer = reinterpret_cast<const char*>(data);
  int total = 0;
  do
    {
    int flags=0;
    int nSent;
    vtkRestartInterruptedSystemCallMacro(
      send(this->SocketDescriptor, buffer+total, length-total, flags),
      nSent);
    if (nSent == vtkSocketErrorReturnMacro)
      {
      vtkSocketErrorMacro(vtkErrnoMacro, "Socket error in call to send.");
      return 0;
      }
    total += nSent;
    } while(total < length);

  return 1;
#else
  static_cast<void>(data);
  static_cast<void>(length);
  return 0;
#endif
}
