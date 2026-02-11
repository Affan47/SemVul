get_unused_database_name(const Glib::ustring& base_name)
{
  Glom::ConnectionPool* connection_pool = Glom::ConnectionPool::get_instance();
  if(!connection_pool)
    return Glib::ustring();

  bool keep_trying = true;
  size_t extra_num = 0;
  while(keep_trying)
  {
    Glib::ustring database_name_possible;
    if(extra_num == 0)
    {


      database_name_possible = Utils::trim_whitespace(base_name);
      database_name_possible = Utils::string_replace(database_name_possible, "\"", "");
      database_name_possible = Utils::string_replace(database_name_possible, "'", "");
      database_name_possible = Utils::string_replace(database_name_possible, "\t", "");
      database_name_possible = Utils::string_replace(database_name_possible, "\n", "");
    }
    else
    {

      const Glib::ustring pchExtraNum = Glib::ustring::compose("%1", extra_num);
      database_name_possible = (base_name + pchExtraNum);
    }
    ++extra_num;

    connection_pool->set_database(database_name_possible);
    connection_pool->set_ready_to_connect();

    Glom::sharedptr<Glom::SharedConnection> connection;

    try
    {
      connection = ConnectionPool::get_and_connect();
    }
    catch(const ExceptionConnection& ex)
    {
      if(ex.get_failure_type() == ExceptionConnection::FAILURE_NO_SERVER)
      {


        std::cerr << G_STRFUNC << ": Could not connect to the server." << std::endl;
        return Glib::ustring();
      }
      else
      {


        return database_name_possible;
      }
    }
  }

  return Glib::ustring();
}
