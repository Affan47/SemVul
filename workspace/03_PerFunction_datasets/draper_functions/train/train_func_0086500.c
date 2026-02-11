on_bar_thick_activate             (GtkToolButton   *toolbutton,
                                   gpointer         func_data)
{
  BarData *bar_data = (BarData *) func_data;

  if (bar_data->thickness == MICRO_THICKNESS)
    {

      GObject *thin_obj = gtk_builder_get_object (bar_gtk_builder, "thin");
      gtk_tool_button_set_label_widget (toolbutton, GTK_WIDGET (thin_obj));
      bar_data->thickness = THIN_THICKNESS;
    }
  else if (bar_data->thickness == THIN_THICKNESS)
    {

      GObject *medium_obj = gtk_builder_get_object (bar_gtk_builder, "medium");
      gtk_tool_button_set_label_widget (toolbutton, GTK_WIDGET (medium_obj));
      bar_data->thickness = MEDIUM_THICKNESS;
    }
  else if (bar_data->thickness==MEDIUM_THICKNESS)
    {

      GObject *thick_obj = gtk_builder_get_object (bar_gtk_builder, "thick");
      gtk_tool_button_set_label_widget (toolbutton, GTK_WIDGET (thick_obj));
      bar_data->thickness = THICK_THICKNESS;
    }
  else if (bar_data->thickness==THICK_THICKNESS)
    {

      GObject *micro_obj = gtk_builder_get_object (bar_gtk_builder, "micro");
      gtk_tool_button_set_label_widget (toolbutton, GTK_WIDGET (micro_obj));
      bar_data->thickness = MICRO_THICKNESS;
    }

}
