select_item(const Glib::ustring& strItemText, guint column, bool start_editing)
{
  Gtk::TreeModel::iterator iter = get_row(strItemText);
  if(iter)
  {
    return select_item(iter, column, start_editing);
  }

  return false;
}
