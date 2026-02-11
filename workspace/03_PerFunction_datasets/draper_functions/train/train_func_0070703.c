add_group(const Document* document, const Glib::ustring& group, bool superuser)
{
  if(!document)
  {
    std::cerr << G_STRFUNC << ": document is null." << std::endl;
    return false;
  }

  if(group.empty())
  {
    std::cerr << G_STRFUNC << ": group is empty." << std::endl;
    return false;
  }

  const Glib::ustring strQuery = DbUtils::build_query_create_group(group, superuser);

  const bool test = DbUtils::query_execute_string(strQuery);
  if(!test)
  {
    std::cerr << G_STRFUNC << ": CREATE GROUP failed." << std::endl;
    return false;
  }


  Privileges priv;
  priv.m_view = true;
  priv.m_edit = true;

  const type_vec_strings table_list =
    get_table_names_from_database(true );
  for(type_vec_strings::const_iterator iter = table_list.begin(); iter != table_list.end(); ++iter)
  {
    if(!Privs::set_table_privileges(group, *iter, priv))
    {
      std::cerr << G_STRFUNC << "Privs::set_table_privileges() failed." << std::endl;
      return false;
    }
  }


  if(!Privs::set_table_privileges(group, GLOM_STANDARD_TABLE_AUTOINCREMENTS_TABLE_NAME, priv))
  {
    std::cerr << G_STRFUNC << "Privs::set_table_privileges() failed." << std::endl;
    return false;
  }

  return true;
}
