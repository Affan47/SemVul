get_relationship_display_name() const
{
  Glib::ustring result;

  if(get_has_relationship_name())
    result = get_relationship_name();

  if(get_has_related_relationship_name())
    result += ("::" + get_related_relationship_name());

  return result;
}
