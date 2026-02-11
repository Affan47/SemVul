glade_gtk_tool_item_group_parse_finished (GladeProject * project,
					  GladeWidget * widget)
{
  GtkWidget *label_widget = NULL;

  glade_widget_property_get (widget, "label-widget", &label_widget);

  if (label_widget)
    glade_widget_property_set (widget, "custom-label", TRUE);
  else
    glade_widget_property_set (widget, "custom-label", FALSE);
}
