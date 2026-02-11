create_local_image_uri(const Gnome::Gda::Value& value)
{
  static guint m_temp_image_uri_number = 0;

  Glib::ustring result;

  if(value.get_value_type() == GDA_TYPE_BINARY)
  {
    long size = 0;
    gconstpointer pData = value.get_binary(size);
    if(size && pData)
    {


      char pchExtraNum[10];
      sprintf(pchExtraNum, "%d", m_temp_image_uri_number);
      result = ("/tmp/glom_report_image_" + Glib::ustring(pchExtraNum) + ".png");
      ++m_temp_image_uri_number;

      std::fstream the_stream(result.c_str(), std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
      if(the_stream)
      {
        the_stream.write((char*)pData, size);
      }
    }
    else
       std::cerr << G_STRFUNC << ": binary GdaValue contains no data." << std::endl;
  }


  if(result.empty())
    result = "/tmp/glom_report_image_invalid.png";

  return ("file://" + result);
}
