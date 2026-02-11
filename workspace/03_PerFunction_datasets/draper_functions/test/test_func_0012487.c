glade_tool_item_group_editor_load (GladeEditable * editable, GladeWidget * widget)
{
  GladeToolItemGroupEditor *group_editor = GLADE_TOOL_ITEM_GROUP_EDITOR (editable);
  gboolean custom_label = FALSE;
  GList *l;


  parent_editable_iface->load (editable, widget);


  if (group_editor->embed)
    glade_editable_load (GLADE_EDITABLE (group_editor->embed), widget);

  for (l = group_editor->properties; l; l = l->next)
    glade_editor_property_load_by_widget (GLADE_EDITOR_PROPERTY (l->data),
                                          widget);


  if (widget)
    {
      glade_widget_property_get (widget, "custom-label", &custom_label);

      if (custom_label)
        gtk_toggle_button_set_active
            (GTK_TOGGLE_BUTTON (group_editor->label_widget_radio), TRUE);
      else
        gtk_toggle_button_set_active
            (GTK_TOGGLE_BUTTON (group_editor->label_radio), TRUE);
    }
}
