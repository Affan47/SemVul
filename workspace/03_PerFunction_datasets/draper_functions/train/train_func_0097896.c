glade_gtk_widget_add2group_cb (GtkMenuItem * item, GladeWidget * gwidget)
{
  GladeWidget *group =
      g_object_get_data (G_OBJECT (item), "glade-group-widget");
  GladeWidgetAdaptor *adaptor =
      glade_widget_adaptor_get_by_type (GTK_TYPE_SIZE_GROUP);
  GList *widget_list = NULL, *new_list;
  GladeProperty *property;

  if (group)
    glade_command_push_group (_("Adding %s to Size Group %s"),
			      glade_widget_get_name (gwidget),
                              glade_widget_get_name (group));
  else
    glade_command_push_group (_("Adding %s to a new Size Group"),
                              glade_widget_get_name (gwidget));

  if (!group)

    group =
        glade_command_create (adaptor, NULL, NULL,
                              glade_widget_get_project (gwidget));

  property = glade_widget_get_property (group, "widgets");
  glade_property_get (property, &widget_list);
  new_list = g_list_copy (widget_list);
  if (!g_list_find (widget_list, glade_widget_get_object (gwidget)))
    new_list = g_list_append (new_list, glade_widget_get_object (gwidget));
  glade_command_set_property (property, new_list);

  g_list_free (new_list);

  glade_command_pop_group ();
}
