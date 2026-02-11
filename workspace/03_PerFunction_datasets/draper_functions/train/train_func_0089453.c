set_page_setup(const Glib::RefPtr<Gtk::PageSetup>& page_setup)
{
  m_page_setup = page_setup;
  if(!m_page_setup)
    return;

  update_page_bounds();
  m_modified = true;
}
