Log(LOGLEVEL level, const std::string& text, ...)
{
  MutexLock lock(&m_msgmutex);

  va_list ap;
  va_start(ap, &text);

  vsnprintf(m_msg, MAX_MESSAGE_SIZE, text.c_str(), ap);
  va_end(ap);

  OnLog(level, m_msg);
}
