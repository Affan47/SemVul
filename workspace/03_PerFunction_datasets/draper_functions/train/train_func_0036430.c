row_drop_possible_vfunc(const Gtk::TreeModel::Path& dest, const Gtk::SelectionData& selection_data) const
{


    Glib::RefPtr<Gtk::TreeModel> refThis = Glib::RefPtr<Gtk::TreeModel>(const_cast<TreeStore_Layout*>(this));
    refThis->reference();
    Gtk::TreeModel::Path path_dragged_row;
    Gtk::TreeModel::Path::get_from_selection_data(selection_data, refThis, path_dragged_row);

    if(path_dragged_row == dest)
      return false;


  Gtk::TreeModel::Path dest_parent = dest;
  bool dest_is_not_top_level = dest_parent.up();
  if(!dest_is_not_top_level || dest_parent.empty())
  {


    TreeStore_Layout* unconstThis = const_cast<TreeStore_Layout*>(this);
    const_iterator iter_dragged = unconstThis->get_iter(path_dragged_row);


    if(iter_dragged)
    {
      Gtk::TreeModel::Row row = *iter_dragged;

      sharedptr<LayoutItem> layout_item = row[m_columns.m_col_layout_item];
      sharedptr<LayoutGroup> layout_group = sharedptr<LayoutGroup>::cast_dynamic(layout_item);
      const bool is_group = layout_group;

      return is_group;
    }
  }
  else
  {
    if(dest_parent == path_dragged_row)
      return false;


    TreeStore_Layout* unconstThis = const_cast<TreeStore_Layout*>(this);
    const_iterator iter_dest_parent = unconstThis->get_iter(dest_parent);

    if(iter_dest_parent)
    {
      Gtk::TreeModel::Row row_parent = *iter_dest_parent;

      sharedptr<LayoutItem> layout_item = row_parent[m_columns.m_col_layout_item];
      sharedptr<LayoutGroup> layout_group = sharedptr<LayoutGroup>::cast_dynamic(layout_item);
      const bool is_group = layout_group;

      return is_group;
    }
  }


  return Gtk::TreeStore::row_drop_possible_vfunc(dest, selection_data);
}
