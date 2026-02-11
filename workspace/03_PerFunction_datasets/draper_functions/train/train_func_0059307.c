error(const char* fmt, ...)
{
  va_list va;
  va_start(va, fmt);
  char buf[1024];
  vsnprintf(buf,sizeof(buf)-1,fmt,va);
  buf[sizeof(buf)-1] = 0;
  XmlRpcErrorHandler::getErrorHandler()->error(buf);
}
