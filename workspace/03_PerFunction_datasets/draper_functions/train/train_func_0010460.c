glade_widget_dup_properties (GladeWidget *dest_widget, GList *template_props, gboolean as_load,
			     gboolean copy_parentless, gboolean exact)
{
	GList *list, *properties = NULL;

	for (list = template_props; list && list->data; list = list->next)
	{
		GladeProperty *prop = list->data;

		if (prop->klass->save == FALSE && as_load)
			continue;


		if (prop->klass->parentless_widget && copy_parentless)
		{
			GObject *object = NULL;
			GladeWidget *parentless;

			glade_property_get (prop, &object);

			prop = glade_property_dup (prop, NULL);

			if (object)
			{
				parentless = glade_widget_get_from_gobject (object);

				parentless = glade_widget_dup (parentless, exact);

				glade_widget_set_project (parentless, dest_widget->project);

				glade_property_set (prop, parentless->object);
			}
		}
		else
			prop = glade_property_dup (prop, NULL);


		properties = g_list_prepend (properties, prop);
	}
	return g_list_reverse (properties);
}
