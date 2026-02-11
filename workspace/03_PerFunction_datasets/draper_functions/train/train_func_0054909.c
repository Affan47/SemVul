set_node_attribute_value_as_decimal(xmlpp::Element* node, const Glib::ustring& strAttributeName, guint value, guint value_default)
{
  if((value == value_default) && !node->get_attribute(strAttributeName))
    return;


  std::stringstream thestream;
  thestream.imbue( std::locale::classic() );
  thestream << value;
  const Glib::ustring value_string = thestream.str();

  set_node_attribute_value(node, strAttributeName, value_string);
}
