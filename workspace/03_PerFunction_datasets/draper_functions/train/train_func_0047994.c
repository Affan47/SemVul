sendTCMCommand(const char *fmt, ...)
{
  if(!myDeviceConnection) return false;
  if(myDeviceConnection->getStatus() != ArDeviceConnection::STATUS_OPEN) return false;
  va_list args;
  va_start(args, fmt);
  char buf[32];
  vsnprintf(buf, sizeof(buf)-1, fmt, args);
  buf[sizeof(buf)-1] = 0;
  return myDeviceConnection->write(buf, strlen(buf));
}
