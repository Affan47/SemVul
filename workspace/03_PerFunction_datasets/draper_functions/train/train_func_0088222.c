glade_gtk_expander_post_create (GladeWidgetAdaptor * adaptor,
                                GObject * expander, GladeCreateReason reason)
{
  static GladeWidgetAdaptor *wadaptor = NULL;
  GladeWidget *gexpander, *glabel;
  GtkWidget *label;

  if (wadaptor == NULL)
    wadaptor = glade_widget_adaptor_get_by_type (GTK_TYPE_LABEL);

  if (reason != GLADE_CREATE_USER)
    return;

  g_return_if_fail (GTK_IS_EXPANDER (expander));
  gexpander = glade_widget_get_from_gobject (expander);
  g_return_if_fail (GLADE_IS_WIDGET (gexpander));


  if ((label = gtk_expander_get_label_widget (GTK_EXPANDER (expander))) == NULL
      || (glade_widget_get_from_gobject (label) == NULL))
    {
      glabel = glade_widget_adaptor_create_widget (wadaptor, FALSE,
                                                   "parent", gexpander,
                                                   "project",
                                                   glade_widget_get_project
                                                   (gexpander), NULL);

      glade_widget_property_set (glabel, "label", "expander");

      g_object_set_data (glade_widget_get_object (glabel), "special-child-type", "label_item");
      glade_widget_add_child (gexpander, glabel, FALSE);
    }

  gtk_expander_set_expanded (GTK_EXPANDER (expander), TRUE);

  gtk_container_add (GTK_CONTAINER (expander), glade_placeholder_new ());

}
