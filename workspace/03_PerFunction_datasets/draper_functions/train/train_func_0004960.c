Seeding() const
{
  if( IsFull() || m_flush_failed ) return 1;
  if( arg_file_to_download && !m_current_filter ) return 1;
  return 0;
}
