getCategoryOverride()
{
	for(xmlNode* element = cat_cur->children;
		element != NULL;
		element = element->next)
	{
	  if(element->type == XML_ELEMENT_NODE && (!strcmp((char*)element->name,"element") || !strcmp((char*)element->name, "engine")))
	  {
      if(Utils::Xml::get_property(element, "override") == "yes")
        return true;
    }
	}

  return false;
}
