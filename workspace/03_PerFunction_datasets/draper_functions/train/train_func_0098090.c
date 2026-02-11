glade_property_class_make_string_from_object (GladePropertyClass *
                                              property_class, GObject * object)
{
  GladeWidget *gwidget;
  gchar *string = NULL, *filename;

  if (!object)
    return NULL;

  if (property_class->pspec->value_type == GDK_TYPE_PIXBUF)
    {
      if ((filename = g_object_get_data (object, "GladeFileName")) != NULL)
        string = g_strdup (filename);
    }
  else if ((gwidget = glade_widget_get_from_gobject (object)) != NULL)
    string = g_strdup (glade_widget_get_name (gwidget));
  else
    g_critical ("Object type property refers to an object "
                "outside the project");

  return string;
}
