on_changed()
  {
    bool active = static_cast<Gtk::ToggleButton &>(m_widget).get_active();
    m_settings->set_boolean(m_key, active);
    guard(active);
  }

}
