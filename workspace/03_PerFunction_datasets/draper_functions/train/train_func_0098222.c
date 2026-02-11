gwa_update_properties_from_type (GladeWidgetAdaptor *adaptor,
                                 GType type,
                                 GList **properties,
                                 gboolean is_packing)
{
  gpointer object_class = g_type_class_ref (type);
  GParamSpec **specs = NULL, *spec;
  guint i, n_specs = 0;


  if (is_packing && !g_type_is_a (adaptor->priv->type, GTK_TYPE_CONTAINER))
    return;

  if (is_packing)
    specs = gtk_container_class_list_child_properties (object_class, &n_specs);
  else
    specs = g_object_class_list_properties (object_class, &n_specs);

  for (i = 0; i < n_specs; i++)
    {
      GladePropertyClass *property_class;
      GList *list;


      for (list = *properties; list && list->data; list = list->next)
        {
          property_class = GLADE_PROPERTY_CLASS (list->data);
          if (glade_property_class_id (property_class) != NULL &&
              g_ascii_strcasecmp (specs[i]->name, glade_property_class_id (property_class)) == 0)
            break;
        }

      if (list == NULL && (spec = pspec_dup (specs[i])))
        {
          property_class = glade_property_class_new (adaptor, spec->name);

	  glade_property_class_set_pspec (property_class, spec);


          spec->owner_type = adaptor->priv->type;


	  glade_property_class_set_virtual (property_class, TRUE);
	  glade_property_class_set_ignore (property_class, TRUE);

	  glade_property_class_set_tooltip (property_class, g_param_spec_get_blurb (spec));
	  glade_property_class_set_name (property_class, g_param_spec_get_nick (spec));

          if (spec->flags & G_PARAM_CONSTRUCT_ONLY)
	    glade_property_class_set_construct_only (property_class, TRUE);

	  glade_property_class_load_defaults_from_spec (property_class);
	  glade_property_class_set_is_packing (property_class, is_packing);

          *properties = g_list_append (*properties, property_class);
        }
    }

  g_free (specs);
}
