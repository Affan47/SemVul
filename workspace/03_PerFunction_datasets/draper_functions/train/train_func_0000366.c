get_node_attribute_value_as_decimal_double(const xmlpp::Element* node, const Glib::ustring& strAttributeName)
{
  double result = 0;
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
