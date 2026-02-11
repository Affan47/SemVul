verbose(const int level, const char*fmt,...) const
{
  char buf[MAXPDSTRING];
  va_list ap;
  va_start(ap, fmt);
  vsnprintf(buf, MAXPDSTRING-1, fmt, ap);
  va_end(ap);

#if defined PD_MINOR_VERSION && (PD_MAJOR_VERSION > 1 || PD_MINOR_VERSION > 38)
  if(NULL!=m_objectname && NULL!=m_objectname->s_name && &s_ != m_objectname){
    ::verbose(level, "[%s]: %s", m_objectname->s_name, buf);
  } else {
    ::verbose(level, "%s", buf);
  }
#else
    if(NULL!=m_objectname && NULL!=m_objectname->s_name && &s_ != m_objectname){
    ::post("[%s]: %s", m_objectname->s_name, buf);
  } else {
    ::post("%s", buf);
  }
#endif
}
