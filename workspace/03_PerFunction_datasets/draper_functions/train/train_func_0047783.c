custom_toggled (GtkWidget * widget, GladeToolButtonEditor * button_editor)
{
  GladeToolButtonEditorPrivate *priv = button_editor->priv;
  GladeProperty *property;
  GladeWidget   *gwidget = glade_editable_loaded_widget (GLADE_EDITABLE (button_editor));

  if (glade_editable_loading (GLADE_EDITABLE (button_editor)) || !gwidget)
    return;

  if (!gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (priv->custom_radio)))
    return;

  glade_editable_block (GLADE_EDITABLE (button_editor));

  glade_command_push_group (_("Setting %s to use an image from the icon theme"),
                            glade_widget_get_name (gwidget));

  property = glade_widget_get_property (gwidget, "stock-id");
  glade_command_set_property (property, NULL);
  property = glade_widget_get_property (gwidget, "icon-name");
  glade_command_set_property (property, NULL);
  property = glade_widget_get_property (gwidget, "icon");
  glade_command_set_property (property, NULL);
  property = glade_widget_get_property (gwidget, "image-mode");
  glade_command_set_property (property, GLADE_TB_MODE_CUSTOM);

  glade_command_pop_group ();

  glade_editable_unblock (GLADE_EDITABLE (button_editor));


  glade_editable_load (GLADE_EDITABLE (button_editor), gwidget);
}
