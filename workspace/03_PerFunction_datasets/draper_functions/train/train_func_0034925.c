remove_item(const Gtk::TreeModel::iterator& iter)
{
  if(iter)
    m_refListStore->erase(iter);
}
