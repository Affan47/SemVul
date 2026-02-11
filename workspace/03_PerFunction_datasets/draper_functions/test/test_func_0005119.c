meta_gtk_widget_get_font_desc (GtkWidget *widget,
                               double     scale,
			       const PangoFontDescription *override)
{
  GtkStyleContext *style;
  PangoFontDescription *font_desc;

  g_return_val_if_fail (gtk_widget_get_realized (widget), NULL);

  style = gtk_widget_get_style_context (widget);
  gtk_style_context_get (style, GTK_STATE_FLAG_NORMAL, "font", &font_desc, NULL);

  if (override)
    pango_font_description_merge (font_desc, override, TRUE);

  pango_font_description_set_size (font_desc,
                                   MAX (pango_font_description_get_size (font_desc) * scale, 1));

  return font_desc;
}
