refresh_from_database_blank()
{
  if(m_find_mode)
    return refresh_from_database();

  if(m_refListStore)
  {
    m_refListStore->clear();
  }

  return true;
}
