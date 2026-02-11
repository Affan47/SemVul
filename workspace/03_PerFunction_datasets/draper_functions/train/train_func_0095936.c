prepare_create_database(const Glib::ustring& provider,
                                                                       const Glib::ustring& db_name)
{
  GError* gerror = 0;
  Glib::RefPtr<ServerOperation> op =
    Glib::wrap(gda_server_operation_prepare_create_database(provider.c_str(), db_name.c_str(), &gerror));

  if(gerror) ::Glib::Error::throw_exception(gerror);

  return op;
}
