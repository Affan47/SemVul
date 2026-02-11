glade_gtk_widget_write_atk_property (GladeProperty * property,
                                     GladeXmlContext * context,
                                     GladeXmlNode * node)
{
  GladeXmlNode *prop_node;
  GladePropertyClass *pclass;
  gchar *value;

  glade_property_get (property, &value);
  if (value && value[0])
    {
      pclass = glade_property_get_class (property);

      prop_node = glade_xml_node_new (context, GLADE_TAG_A11Y_PROPERTY);
      glade_xml_node_append_child (node, prop_node);

      glade_xml_node_set_property_string (prop_node,
                                          GLADE_TAG_NAME, glade_property_class_id (pclass));

      glade_xml_set_content (prop_node, value);

      if (glade_property_i18n_get_translatable (property))
        glade_xml_node_set_property_string (prop_node,
                                            GLADE_TAG_TRANSLATABLE,
                                            GLADE_XML_TAG_I18N_TRUE);

      if (glade_property_i18n_get_comment (property))
        glade_xml_node_set_property_string (prop_node,
                                            GLADE_TAG_COMMENT,
                                            glade_property_i18n_get_comment (property));

      if (glade_property_i18n_get_context (property))
        glade_xml_node_set_property_string (prop_node,
                                            GLADE_TAG_CONTEXT,
                                            glade_property_i18n_get_context (property));
    }
}
