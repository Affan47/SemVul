gpc_read_displayable_values_from_node (GladeXmlNode * node,
                                       GladePropertyClass * klass,
                                       const gchar * domain)
{
  gpointer the_class = g_type_class_ref (klass->pspec->value_type);
  GladeXmlNode *child;
  GEnumValue *enum_values = NULL;
  GFlagsValue *flags_values = NULL;
  gint n_values, registered_values = 0;

  if (G_IS_PARAM_SPEC_ENUM (klass->pspec))
    {
      GEnumClass *eclass = the_class;
      enum_values = eclass->values;
      n_values = eclass->n_values;
    }
  else
    {
      GFlagsClass *fclass = the_class;
      flags_values = fclass->values;
      n_values = fclass->n_values;
    }

  if ((child = glade_xml_search_child (node, GLADE_TAG_VALUE)) == NULL)
    return;

  for (child = glade_xml_node_get_children (node); child; child = glade_xml_node_next (child))
    {
      gint i;
      gchar *id, *name;
      GEnumValue *enum_val;
      GFlagsValue *flags_val;
      gboolean disabled;

      id = glade_xml_get_property_string_required (child, GLADE_TAG_ID, NULL);
      if (!id) continue;

      disabled = glade_xml_get_property_boolean (child, GLADE_TAG_DISABLED, FALSE);

      if (!disabled)
        {
          name = glade_xml_get_property_string_required (child, GLADE_TAG_NAME, NULL);
          if (!name) continue;
        }
      else
        name = NULL;

      for (i = 0; i < n_values; i++)
        {

          if ((G_IS_PARAM_SPEC_ENUM (klass->pspec) &&
               (strcmp (id, enum_values[i].value_name) == 0 ||
                strcmp (id, enum_values[i].value_nick) == 0)) ||
              (G_IS_PARAM_SPEC_FLAGS (klass->pspec) &&
               (strcmp (id, flags_values[i].value_name) == 0 ||
                strcmp (id, flags_values[i].value_nick) == 0)))
            {
              registered_values++;

              if (G_IS_PARAM_SPEC_ENUM (klass->pspec))
                {
                  enum_val = &enum_values[i];
                  glade_register_displayable_value (klass->pspec->value_type,
                                                    enum_val->value_nick,
                                                    domain, name);
                  if (disabled)
                    glade_displayable_value_set_disabled (klass->pspec->value_type,
                                                          enum_val->value_nick,
                                                          TRUE);
                }
              else
                {
                  flags_val = &flags_values[i];
                  glade_register_displayable_value (klass->pspec->value_type,
                                                    flags_val->value_nick,
                                                    domain, name);
                  if (disabled)
                    glade_displayable_value_set_disabled (klass->pspec->value_type,
                                                          flags_val->value_nick,
                                                          TRUE);
                }
              break;
            }
        }

      g_free (id);
      g_free (name);
    }

  if (n_values != registered_values)
    g_message ("%d missing displayable value for %s::%s",
               n_values - registered_values,
               glade_widget_adaptor_get_name (klass->adaptor), klass->id);

  g_type_class_unref (the_class);

}
