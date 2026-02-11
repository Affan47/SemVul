setup()
  {
    m_connection.block();
    static_cast<Gtk::ToggleButton &>(m_widget).set_active(m_settings->get_boolean(m_key));
    m_connection.unblock();
  }
