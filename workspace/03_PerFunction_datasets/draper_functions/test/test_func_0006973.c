label_widget_toggled (GtkWidget * widget, GladeToolItemGroupEditor * group_editor)
{
  GladeProperty *property;
  GladeWidget   *gwidget = glade_editable_loaded_widget (GLADE_EDITABLE (group_editor));

  if (glade_editable_loading (GLADE_EDITABLE (group_editor)) || !gwidget)
    return;

  if (!gtk_toggle_button_get_active
      (GTK_TOGGLE_BUTTON (group_editor->label_widget_radio)))
    return;

  glade_editable_block (GLADE_EDITABLE (group_editor));

  glade_command_push_group (_("Setting %s to use a custom label widget"),
                            glade_widget_get_name (gwidget));

  property = glade_widget_get_property (gwidget, "label");
  glade_command_set_property (property, NULL);
  property = glade_widget_get_property (gwidget, "custom-label");
  glade_command_set_property (property, TRUE);

  glade_command_pop_group ();

  glade_editable_unblock (GLADE_EDITABLE (group_editor));


  glade_editable_load (GLADE_EDITABLE (group_editor), gwidget);
}
