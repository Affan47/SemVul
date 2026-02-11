get_selected_group_parent() const
{


  Gtk::TreeModel::iterator parent;

  Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = m_treeview_fields->get_selection();
  if(refTreeSelection)
  {
    Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
    if(iter)
    {
      Gtk::TreeModel::Row row = *iter;

      sharedptr<LayoutItem> layout_item = row[m_model_items->m_columns.m_col_layout_item];
      sharedptr<LayoutGroup> layout_group = sharedptr<LayoutGroup>::cast_dynamic(layout_item);
      sharedptr<LayoutItem_Portal> layout_portal = sharedptr<LayoutItem_Portal>::cast_dynamic(layout_item);

      if(layout_group && !layout_portal)
      {

        parent = iter;
      }
      else
      {

        parent = iter->parent();
      }
    }
  }

  return parent;
}
