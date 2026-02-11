on_cell_layout_button_clicked(const Gtk::TreeModel::Path& path, int model_column_index)
{
  if(!m_refListStore)
    return;

  Gtk::TreeModel::iterator iter = m_refListStore->get_iter(path);
  if(iter)
  {
    sharedptr<const LayoutItem> layout_item = m_column_items[model_column_index];
    sharedptr<const LayoutItem_Button> item_button = sharedptr<const LayoutItem_Button>::cast_dynamic(layout_item);
    if(item_button)
    {
      m_signal_script_button_clicked.emit(item_button, iter);
    }
  }
}
