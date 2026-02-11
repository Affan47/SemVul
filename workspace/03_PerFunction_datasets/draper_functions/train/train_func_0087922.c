buffer_toggled (GtkWidget * widget, GladeEntryEditor * entry_editor)
{
  GladeEntryEditorPrivate *priv = entry_editor->priv;
  GladeProperty *property;
  GladeWidget   *gwidget = glade_editable_loaded_widget (GLADE_EDITABLE (entry_editor));

  if (glade_editable_loading (GLADE_EDITABLE (entry_editor)) || !gwidget)
    return;

  if (!gtk_toggle_button_get_active
      (GTK_TOGGLE_BUTTON (priv->buffer_radio)))
    return;

  glade_editable_block (GLADE_EDITABLE (entry_editor));

  glade_command_push_group (_("Setting %s to use an external buffer"),
                            glade_widget_get_name (gwidget));


  property = glade_widget_get_property (gwidget, "text");
  glade_command_set_property (property, NULL);

  property = glade_widget_get_property (gwidget, "use-entry-buffer");
  glade_command_set_property (property, TRUE);

  glade_command_pop_group ();

  glade_editable_unblock (GLADE_EDITABLE (entry_editor));


  glade_editable_load (GLADE_EDITABLE (entry_editor), gwidget);
}
