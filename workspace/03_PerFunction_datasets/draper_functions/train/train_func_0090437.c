on_name_acquired(const Glib::RefPtr<Gio::DBus::Connection> & conn, const Glib::ustring &)
{
  try {
    if(s_bus_acquired) {
      register_object(conn, *s_manager, s_on_name_acquire_finish);
      return;
    }
  }
  catch(Glib::Exception & e) {
    DBG_OUT("Failed to acquire name: %s", e.what().c_str());
  }

  s_on_name_acquire_finish(false, false);
}
