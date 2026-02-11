FileChooserDialog_SaveExtras(Gtk::Window& parent, const Glib::ustring& title, Gtk::FileChooserAction action, const Glib::ustring& backend)
: Gtk::FileChooserDialog(parent, title, action, backend),
  m_extra_widget(Gtk::ORIENTATION_VERTICAL)
{
  create_child_widgets();
}
