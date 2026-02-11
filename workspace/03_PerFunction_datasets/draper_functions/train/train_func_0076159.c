fill_list()
{

  m_model_users->clear();

  if(m_combo_group)
  {
    const Glib::ustring group_name = m_combo_group->get_active_text();
    const type_vec_strings user_list = Privs::get_database_users(group_name);
    for(type_vec_strings::const_iterator iter = user_list.begin(); iter != user_list.end(); ++iter)
    {
      Gtk::TreeModel::iterator iterTree = m_model_users->append();
      Gtk::TreeModel::Row row = *iterTree;

      row[m_model_columns_users.m_col_name] = Privs::get_user_visible_group_name(*iter);
    }
  }
}
