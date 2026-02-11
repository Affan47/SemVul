fill_from_database()
{
  BusyCursor busy_cursor(get_app_window());

  const bool result = Base_DB_Table_Data::fill_from_database();
  if(!result)
    return false;


  create_layout();

  m_FieldsShown = get_fields_to_show();

  return result;
}
