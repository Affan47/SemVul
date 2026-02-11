fill_from_database()
{
  bool result = Box_DB_Table::fill_from_database();
  if(!result)
  {
    std::cerr << G_STRFUNC << ":  Box_DB_Table::fill_from_database() failed." << std::endl;
    return false;
  }

  if(!(ConnectionPool::get_instance()->get_ready_to_connect()))
    return false;

  fill_fields();

  try
  {

    m_AddDel.remove_all();

    Field::type_map_type_names mapFieldTypes = Field::get_type_names_ui();

    for(type_vec_fields::iterator iter = m_vecFields.begin(); iter != m_vecFields.end(); ++iter)
    {
      const sharedptr<const Field>& field = *iter;


      Gtk::TreeModel::iterator tree_iter= m_AddDel.add_item(field->get_name());
      fill_field_row(tree_iter, field);
    }

    result = true;
  }
  catch(const Glib::Exception& ex)
  {
    handle_error(ex);
    result = false;
  }
  catch(const std::exception& ex)
  {
    handle_error(ex);
    result = false;
  }

  return result;
}
