get_node_attribute_value_as_value(const xmlpp::Element* node, const Glib::ustring& strAttributeName, Field::glom_field_type field_type)
{
  const Glib::ustring value_string = get_node_attribute_value(node, strAttributeName);

  bool success = false;
  const Gnome::Gda::Value result = Field::from_file_format(value_string, field_type, success);
  if(success)
    return result;
  else
    return Gnome::Gda::Value();
}
