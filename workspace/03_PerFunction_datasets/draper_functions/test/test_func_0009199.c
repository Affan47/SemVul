get_developer_user_exists_with_password()
{
  Glib::ustring default_password;
  const Glib::ustring default_user = get_default_developer_user_name(default_password);

  const type_vec_strings users = get_database_users();
  for(type_vec_strings::const_iterator iter = users.begin(); iter != users.end(); ++iter)
  {
    const Glib::ustring user = *iter;
    if(user == default_user)
      continue;

    if(get_user_is_in_group(user, GLOM_STANDARD_GROUP_NAME_DEVELOPER))
      return true;
  }

  return false;
}
