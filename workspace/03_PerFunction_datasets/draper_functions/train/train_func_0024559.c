parse_value(Field::glom_field_type glom_type, const Glib::ustring& text, bool& success, bool iso_format)
{
  NumericFormat ignore_format;
  return parse_value(glom_type, text, ignore_format, success, iso_format);
}
