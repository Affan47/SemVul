Switch(const Glib::ustring& base_name):

  Glib::ObjectBase(0),
  Gtk::ToggleButton(Glib::ConstructParams(switch_class_.init(), "base_name",base_name.c_str(), static_cast<char*>(0)))
{}
