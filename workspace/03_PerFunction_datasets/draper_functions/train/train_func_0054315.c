get_groups_of_user(const Glib::ustring& user)
{


  type_vec_strings result;


  type_vec_strings groups = get_database_groups();
  for(type_vec_strings::const_iterator iter = groups.begin(); iter != groups.end(); ++iter)
  {

    if(get_user_is_in_group(user, *iter))
    {

      result.push_back(*iter);
    }
  }

  return result;
}
