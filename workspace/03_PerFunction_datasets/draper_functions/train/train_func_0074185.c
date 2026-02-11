glade_image_item_editor_load (GladeEditable * editable, GladeWidget * widget)
{
  GladeImageItemEditor *item_editor = GLADE_IMAGE_ITEM_EDITOR (editable);
  GladeWidget *image_widget;
  GList *l;
  gboolean use_stock = FALSE;


  parent_editable_iface->load (editable, widget);


  if (item_editor->embed)
    glade_editable_load (GLADE_EDITABLE (item_editor->embed), widget);

  if (item_editor->embed_image)
    {

      if (widget && (image_widget = get_image_widget (widget)))
        glade_editable_load (GLADE_EDITABLE (item_editor->embed_image),
                             image_widget);
      else
        glade_editable_load (GLADE_EDITABLE (item_editor->embed_image), NULL);
    }
  for (l = item_editor->properties; l; l = l->next)
    glade_editor_property_load_by_widget (GLADE_EDITOR_PROPERTY (l->data),
                                          widget);

  if (widget)
    {
      glade_widget_property_get (widget, "use-stock", &use_stock);

      gtk_widget_set_sensitive (item_editor->embed_frame, !use_stock);
      gtk_widget_set_sensitive (item_editor->label_frame, !use_stock);

      if (use_stock)
        gtk_toggle_button_set_active
            (GTK_TOGGLE_BUTTON (item_editor->stock_radio), TRUE);
      else
        gtk_toggle_button_set_active
            (GTK_TOGGLE_BUTTON (item_editor->custom_radio), TRUE);
    }
}
