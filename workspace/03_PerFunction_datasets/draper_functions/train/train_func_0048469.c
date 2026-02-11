gnac_profiles_xml_engine_get_combo_values(XMLDoc      *doc,
                                          const gchar *expr)
{
  xmlXPathObjectPtr xpath_obj = gnac_profiles_xml_engine_evaluate_query(
      expr, doc->xpath_context);
  if (!xpath_obj) return NULL;

  xmlNodeSetPtr nodes = xpath_obj->nodesetval;
  if (xmlXPathNodeSetIsEmpty(nodes)) {
    xmlXPathFreeObject(xpath_obj);
    return NULL;
  }

  xmlNode *values_first = NULL;
  xmlNode *values_last = NULL;
  gchar   *default_value = NULL;
  gchar   *variable_name = NULL;

  xmlNodePtr current_node = nodes->nodeTab[0]->children;

  while ((current_node = current_node->next)) {
    gchar *content = (gchar *) xmlNodeGetContent(current_node->children);

    if (gnac_profiles_xml_engine_node_name_equal(current_node,
        "variable-name"))
    {
      variable_name = g_strdup(content);
    }
    else if (gnac_profiles_xml_engine_node_name_equal(current_node,
        "default-value"))
    {
      default_value = g_strdup(content);
    }
    else if (gnac_profiles_xml_engine_node_name_equal(current_node,
        "possible-values"))
    {
      values_first = current_node->children->next;
      values_last = current_node->last;
    }

    g_free(content);
  }

  if (values_first && values_last && default_value && variable_name) {
    GList *values = NULL;
    GList *names = NULL;

    xmlNode *current_node = values_first;

    while (current_node && current_node != values_last) {
      if (!gnac_profiles_xml_engine_is_i18n_node(current_node)) {
        values = g_list_prepend(values,
            xmlNodeGetContent(current_node->properties->children));
        xmlChar *content = xmlNodeGetContent(current_node->children);
        names = g_list_prepend(names, g_strdup(gettext((gchar *) content)));
        xmlFree(content);
      }

      current_node = current_node->next;

      if (xmlNodeIsText(current_node)) {
        current_node = current_node->next;
      }
    }

    xmlXPathFreeObject(xpath_obj);

    ComboValues *combo_values = g_malloc(sizeof(ComboValues));
    combo_values->names = g_list_reverse(names);
    combo_values->values = g_list_reverse(values);
    combo_values->default_value = default_value;
    combo_values->variable_name = variable_name;

    return combo_values;
  }

  xmlXPathFreeObject(xpath_obj);

  return NULL;
}
