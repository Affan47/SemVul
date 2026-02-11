get_selected_group() const
{
  Glib::RefPtr<Gtk::TreeView::Selection> refSelection = m_treeview_groups->get_selection();
  if(refSelection)
  {
    Gtk::TreeModel::iterator iter = refSelection->get_selected();
    if(iter)
    {
      Gtk::TreeModel::Row row = *iter;
      return row[m_model_columns_groups.m_col_name];
    }
  }

  return Glib::ustring();
}
