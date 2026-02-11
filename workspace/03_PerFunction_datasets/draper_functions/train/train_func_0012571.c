get_suitable_table_to_view_details(Glib::ustring& table_name, sharedptr<const UsesRelationship>& relationship, const Document* document) const
{

  table_name = Glib::ustring();

  sharedptr<const UsesRelationship> navigation_relationship;


  if(get_navigation_type() == LayoutItem_Portal::NAVIGATION_AUTOMATIC)
  {


    navigation_relationship = get_portal_navigation_relationship_automatic(document);


  }
  else
  {
    navigation_relationship = get_navigation_relationship_specific();

  }


  const Glib::ustring directly_related_table_name = get_table_used(Glib::ustring() );


  Glib::ustring navigation_table_name;
  if(navigation_relationship)
  {
    navigation_table_name = navigation_relationship->get_table_used(directly_related_table_name);
  }
  else if(get_navigation_type() != LayoutItem_Portal::NAVIGATION_NONE)
  {


    navigation_table_name = directly_related_table_name;
  }

  if(navigation_table_name.empty())
  {

    return;
  }

  if(!document)
  {
    std::cerr << G_STRFUNC << ": document is null" << std::endl;
    return;
  }

  if(document->get_table_is_hidden(navigation_table_name))
  {
    std::cerr << G_STRFUNC << ": navigation_table_name indicates a hidden table: " << navigation_table_name << std::endl;
    return;
  }

  table_name = navigation_table_name;
  relationship = navigation_relationship;
}
