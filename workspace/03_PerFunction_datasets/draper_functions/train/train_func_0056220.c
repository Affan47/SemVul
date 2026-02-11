onRangeChanged(GtkRange *rg, gpointer data)
{
  float val;

  val = (float)gtk_range_get_value(rg);
#if GTK_MAJOR_VERSION == 2 && GTK_MINOR_VERSION < 11
  if (GTK_WIDGET(rg) == rangeHlStart &&
      val > gtk_range_get_value(GTK_RANGE(data)))
    gtk_range_set_value(rg, gtk_range_get_value(GTK_RANGE(data)));
#endif
  if (GTK_WIDGET(rg) == rangeHlEnd)
    {
      if (val < gtk_range_get_value(GTK_RANGE(data)))
	{
	  gtk_range_set_value(rg, gtk_range_get_value(GTK_RANGE(data)));
	  val = gtk_range_get_value(GTK_RANGE(data));
	}
#if GTK_MAJOR_VERSION > 2 || GTK_MINOR_VERSION > 11
      gtk_range_set_fill_level(GTK_RANGE(data), val);
#endif
    }
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkHighlight), FALSE);

  if (setHlRange(TRUE))
    visu_ui_curve_frame_draw(VISU_UI_CURVE_FRAME(curve));
}
