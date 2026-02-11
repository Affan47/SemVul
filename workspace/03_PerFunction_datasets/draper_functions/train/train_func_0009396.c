on_cell_button_clicked(const Gtk::TreeModel::Path& path)
{
  if(!m_refListStore)
    return;

  Gtk::TreeModel::iterator iter = m_refListStore->get_iter(path);
  if(iter)
  {
    select_item(iter, false );
  }


  Glib::signal_idle().connect_once(
    sigc::mem_fun(*this, &DbAddDel::on_idle_row_edit));
}
