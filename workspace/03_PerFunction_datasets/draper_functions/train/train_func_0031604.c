set_relationships(const type_vec_relationships& relationships, const Glib::ustring& parent_table_name, const Glib::ustring& parent_table_title)
{
  m_model->clear();

  set_display_parent_table(parent_table_name, parent_table_title);


  for(type_vec_relationships::const_iterator iter = relationships.begin(); iter != relationships.end(); ++iter)
  {
    Gtk::TreeModel::iterator tree_iter = m_model->append();
    Gtk::TreeModel::Row row = *tree_iter;

    row[m_model_columns.m_relationship] = *iter;
    row[m_model_columns.m_separator] = false;
  }
}
