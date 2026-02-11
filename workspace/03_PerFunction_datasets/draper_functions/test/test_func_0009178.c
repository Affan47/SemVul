get_current_privs(const Glib::ustring& table_name)
{
  if(table_name.empty())
  {
    std::cerr << G_STRFUNC << ": table_name is empty." << std::endl;
    return Privileges();
  }


  type_map_privileges::const_iterator iter = m_privileges_cache.find(table_name);
  if(iter != m_privileges_cache.end())
  {

    return iter->second;
  }


  Privileges result;


  ConnectionPool* connection_pool = ConnectionPool::get_instance();
  const Glib::ustring current_user = connection_pool->get_user();


  sharedptr<SharedConnection> sharedconnection = connection_pool->connect();
  if(sharedconnection && sharedconnection->get_gda_connection()->supports_feature(Gnome::Gda::CONNECTION_FEATURE_USERS))
  {

    type_vec_strings groups = get_groups_of_user(current_user);
    for(type_vec_strings::const_iterator iter = groups.begin(); iter != groups.end(); ++iter)
    {
      Privileges privs = get_table_privileges(*iter, table_name);

      if(privs.m_view)
        result.m_view = true;

      if(privs.m_edit)
        result.m_edit = true;

      if(privs.m_create)
        result.m_create = true;

      if(privs.m_delete)
        result.m_delete = true;
    }
  }
  else
  {

    result.m_view = true;
    result.m_edit = true;
    result.m_create = true;
    result.m_delete = true;
  }

  m_privileges_cache[table_name] = result;


  type_map_cache_timeouts::iterator iter_connection = m_map_cache_timeouts.find(table_name);
  if(iter_connection != m_map_cache_timeouts.end())
    iter_connection->second.disconnect();

  m_map_cache_timeouts[table_name] =
    Glib::signal_timeout().connect_seconds(
      sigc::bind( sigc::ptr_fun(&Privs::on_privs_privileges_cache_timeout), table_name ),
      30 );

  return result;
}

}
