simo_combo_box_get_line_height(SimoComboBox *combo_box)
{
  if (combo_box->priv->cached_line_height == 0) {
    PangoLayout    *layout;
    PangoRectangle  logical_rect;

    layout = gtk_widget_create_pango_layout(GTK_WIDGET(combo_box->txtview), "W");
    pango_layout_get_pixel_extents(layout, NULL, &logical_rect);
    combo_box->priv->cached_line_height = logical_rect.height;
    g_object_unref(layout);
  }

  return combo_box->priv->cached_line_height;
}
