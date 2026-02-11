go_option_menu_get_props (GOOptionMenu       *option_menu,
			   GOOptionMenuProps  *props)
{
  GtkRequisition *indicator_size;
  GtkBorder *indicator_spacing;

  gtk_widget_style_get (GTK_WIDGET (option_menu),
			"indicator_size", &indicator_size,
			"indicator_spacing", &indicator_spacing,
			"interior_focus", &props->interior_focus,
			"focus_line_width", &props->focus_width,
			"focus_padding", &props->focus_pad,
			NULL);

  if (indicator_size)
    props->indicator_size = *indicator_size;
  else
    props->indicator_size = default_props.indicator_size;

  if (indicator_spacing)
    props->indicator_spacing = *indicator_spacing;
  else
    props->indicator_spacing = default_props.indicator_spacing;

  g_free (indicator_size);
  g_free (indicator_spacing);
}
