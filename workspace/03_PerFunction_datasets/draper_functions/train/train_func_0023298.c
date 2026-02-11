handle_request_password_connection_error(bool asked_for_password, const ExceptionConnection& ex, bool& database_not_found)
{
  std::cerr << G_STRFUNC << ": caught exception." << std::endl;


  database_not_found = false;

  if(asked_for_password && ex.get_failure_type() == ExceptionConnection::FAILURE_NO_SERVER)
  {

    Utils::show_ok_dialog(_("Connection Failed"), _("Glom could not connect to the database server. Maybe you entered an incorrect user name or password, or maybe the postgres database server is not running."), *(get_app_window()), Gtk::MESSAGE_ERROR);
    return true;
  }
  else if(ex.get_failure_type() == ExceptionConnection::FAILURE_NO_DATABASE)
  {
    cleanup_connection();


    database_not_found = true;
    return false;
  }
  else
  {
    std::cerr << G_STRFUNC << ": Unexpected exception: " << ex.what() << std::endl;
    cleanup_connection();
    return false;
  }
}
