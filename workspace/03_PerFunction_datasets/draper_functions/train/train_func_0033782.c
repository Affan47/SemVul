set_primary_key_value_selected(const Gnome::Gda::Value& primary_key_value)
{
  Gtk::TreeModel::iterator iter = m_AddDel.get_row(primary_key_value);
  if(iter)
  {
    m_AddDel.select_item(iter);
  }
}
