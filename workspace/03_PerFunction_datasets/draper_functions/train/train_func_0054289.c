check_postgres_gda_client_is_available()
{


  Glib::RefPtr<Gnome::Gda::DataModel> model = Gnome::Gda::Config::list_providers();
  if(model && model->get_n_columns() && model->get_n_rows())
  {
    Glib::RefPtr<Gnome::Gda::DataModelIter> iter = model->create_iter();

    do
    {


      Gnome::Gda::Value name;
      try
      {
        name = iter->get_value_at(0);
      }
      catch(const Glib::Error& ex)
      {
        std::cerr << G_STRFUNC << ": exception: " << ex.what() << std::endl;
      }

      if(name.get_value_type() != G_TYPE_STRING)
        continue;

      const Glib::ustring name_as_string = name.get_string();

      if(name_as_string == "PostgreSQL")
        return true;
    }
    while(iter->move_next());
  }

  return false;
}
