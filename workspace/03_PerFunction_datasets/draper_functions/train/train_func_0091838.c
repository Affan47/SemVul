RemoteControl_proxy(const Glib::RefPtr<Gio::DBus::Connection> & connection,
                                         const char * name, const char * p, const char * interface_name,
                                         const Glib::RefPtr<Gio::DBus::InterfaceInfo> & gnote_interface)
  : Gio::DBus::Proxy(connection, name, p, interface_name, gnote_interface)
{
}
