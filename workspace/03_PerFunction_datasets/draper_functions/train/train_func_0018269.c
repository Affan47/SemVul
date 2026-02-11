gnac_profiles_xml_engine_get_property(XMLDoc      *doc,
                                      const gchar *query,
                                      const gchar *property_name)
{
  xmlXPathObjectPtr xpath_obj = gnac_profiles_xml_engine_evaluate_query(
      query, doc->xpath_context);
  if (!xpath_obj) return NULL;

  xmlNodeSetPtr nodes = xpath_obj->nodesetval;
  if (xmlXPathNodeSetIsEmpty(nodes)) {
    xmlXPathFreeObject(xpath_obj);
    return NULL;
  }

  xmlChar *property = xmlGetProp(nodes->nodeTab[0], (xmlChar *) property_name);

  xmlXPathFreeObject(xpath_obj);

  return (gchar *) property;
}
