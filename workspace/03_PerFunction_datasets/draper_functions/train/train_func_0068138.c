glade_widget_adaptor_object_create_eprop (GladeWidgetAdaptor *adaptor,
                                          GladePropertyClass *klass,
                                          gboolean use_command)
{
  GladeEditorProperty *eprop;
  GParamSpec          *pspec;
  GType                type = 0;

  pspec = glade_property_class_get_pspec (klass);


  if ((type = glade_widget_adaptor_get_eprop_type (pspec)) == 0)
    return NULL;


  if (glade_property_class_themed_icon (klass))
    type = GLADE_TYPE_EPROP_NAMED_ICON;


  eprop = g_object_new (type,
                        "property-class", klass,
                        "use-command", use_command, NULL);

  return eprop;
}
