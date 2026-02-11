connect(const Glib::ustring& database, const Glib::ustring& username, const Glib::ustring& password, bool fake_connection)
{
  Glib::RefPtr<Gnome::Gda::Connection> connection;
  if(m_database_directory_uri.empty())
    return connection;


  Glib::RefPtr<Gio::File> db_dir = Gio::File::create_for_uri(m_database_directory_uri);
  Glib::RefPtr<Gio::File> db_file = db_dir->get_child(database + ".db");

  const bool file_exists = Glom::Utils::file_exists(db_file);
  if(!file_exists)
  {


  }
  else
  {
    if(db_file->query_file_type() != Gio::FILE_TYPE_REGULAR)
    {
      std::cerr << G_STRFUNC << ": The db file is not a regular file at path: " << db_file->get_uri() << std::endl;
    }
    else
    {

      const std::string database_directory = db_dir->get_path();

      const Glib::ustring cnc_string = "DB_DIR=" + DbUtils::gda_cnc_string_encode(database_directory) +
        ";DB_NAME=" + DbUtils::gda_cnc_string_encode(database);
      const Glib::ustring auth_string = Glib::ustring::compose("USERNAME=%1;PASSWORD=%2",
        DbUtils::gda_cnc_string_encode(username), DbUtils::gda_cnc_string_encode(password));

      if(fake_connection)
      {
         connection = Gnome::Gda::Connection::create_from_string("SQLite",
          cnc_string, auth_string,
          Gnome::Gda::CONNECTION_OPTIONS_SQL_IDENTIFIERS_CASE_SENSITIVE);
      }
      else
      {
        connection = Gnome::Gda::Connection::open_from_string("SQLite",
          cnc_string, auth_string,
          Gnome::Gda::CONNECTION_OPTIONS_SQL_IDENTIFIERS_CASE_SENSITIVE);
      }
    }
  }

  if(!connection)
  {


    if(Glom::Utils::file_exists(db_dir) &&
      (db_dir->query_file_type() == Gio::FILE_TYPE_DIRECTORY))
    {
      throw ExceptionConnection(ExceptionConnection::FAILURE_NO_DATABASE);
    }
    else
      throw ExceptionConnection(ExceptionConnection::FAILURE_NO_SERVER);
  }

  return connection;
}
