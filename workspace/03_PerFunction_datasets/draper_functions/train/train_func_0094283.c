glade_gtk_menu_item_set_property (GladeWidgetAdaptor * adaptor,
                                  GObject * object,
                                  const gchar * id, const GValue * value)
{
  GladeWidget *gwidget = glade_widget_get_from_gobject (object);
  GladeProperty *property = glade_widget_get_property (gwidget, id);

  if (!strcmp (id, "use-underline"))
    glade_gtk_menu_item_set_use_underline (object, value);
  else if (!strcmp (id, "label"))
    glade_gtk_menu_item_set_label (object, value);
  else if (GPC_VERSION_CHECK
           (glade_property_get_class (property), gtk_major_version, gtk_minor_version + 1))
    GWA_GET_CLASS (GTK_TYPE_CONTAINER)->set_property (adaptor, object, id,
                                                      value);
}
