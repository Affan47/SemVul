get_first_category()
{
  return Utils::Xml::get_node(doc->children->children, "category");
}
