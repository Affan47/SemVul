ipeDebug(const char *msg, ...)
{
  if (debugHandler) {
    char buf[8196];
    va_list ap;
    va_start(ap, msg);
    std::vsprintf(buf, msg, ap);
    va_end(ap);
    debugHandler(buf);
  }
}
