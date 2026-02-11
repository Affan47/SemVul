add_ui_from_string(const Glib::ustring& ui_description)
{
  try
  {
    m_refUIManager->add_ui_from_string(ui_description);
  }
  catch(const Glib::Error& ex)
  {
    std::cerr << "building menus failed: " <<  ex.what();
  }
}
