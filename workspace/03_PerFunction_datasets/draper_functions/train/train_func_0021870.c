get_node_attribute_value_as_decimal(const xmlpp::Element* node, const Glib::ustring& strAttributeName, guint value_default)
{
  guint result = value_default;
  const Glib::ustring value_string = get_node_attribute_value(node, strAttributeName);


  if(!value_string.empty())
  {
    std::stringstream thestream;
    thestream.imbue( std::locale::classic() );
    thestream.str(value_string);
    thestream >> result;
  }

  return result;
}
