Interact_n(const char *message, ...)
{
  va_list ap;

  if( m_streams[O_INTERACT]->SameDev(m_streams[O_NORMAL]) ){
    if( m_status_last && message && *message ) Interact_n("");
    m_status_last = 0;
  }
  va_start(ap, message);
  if( m_streams[O_INTERACT]->Output_n(message, ap) )
    SyncNewlines(O_INTERACT);
  va_end(ap);
}
