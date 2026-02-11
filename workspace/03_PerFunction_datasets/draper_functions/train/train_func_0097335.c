get_item_selected()
{
  Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = m_TreeView.get_selection();
  if(refTreeSelection)
  {
     return refTreeSelection->get_selected();
  }

  if(m_refListStore)
    return m_refListStore->children().end();
  else
    return Gtk::TreeModel::iterator();
}
