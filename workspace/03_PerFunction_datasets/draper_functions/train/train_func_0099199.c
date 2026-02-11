on_privs_privileges_cache_timeout(const Glib::ustring& table_name)
{


  type_map_privileges::iterator iter = m_privileges_cache.find(table_name);
  if(iter != m_privileges_cache.end())
  {

    m_privileges_cache.erase(iter);
  }

  return false;
}
