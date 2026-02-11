get_link_cell_attributes(const string &href)
{
  if (href.at(0) == '#') {
    static const char internal_link_attributes =
      Formatting::getAttributes("A.attributes.internal_link", Cell::UNDERLINE);
    return internal_link_attributes;
  } else {
    static const char external_link_attributes =
      Formatting::getAttributes("A.attributes.external_link", Cell::UNDERLINE);
    return external_link_attributes;
  }
}
