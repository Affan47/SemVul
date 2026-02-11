Util_DOM_Write(Glib::ustring& refstrXML) const
{
#ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
  try
#endif
  {
    if(m_write_formatted)
      refstrXML = m_pDOM_Document->write_to_string_formatted();
    else
      refstrXML = m_pDOM_Document->write_to_string();
  }
#ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
  catch(xmlpp::exception& ex)
  {
    std::cerr << G_STRFUNC << ": exception caught: " << ex.what() << std::endl;
  }
#endif
}
