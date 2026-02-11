led_bar_new (gint segments, gint orientation )
{
  LedBar    *led_bar;
  GtkWidget *table;
  gint      i;
  GdkColor  active;
  GdkColor  inactive;
  gint      half, full;

  led_bar = gtk_type_new (led_bar_get_type ());
  if (segments > MAX_SEGMENTS)
    segments = MAX_SEGMENTS;
  led_bar->num_segments = segments;
  led_bar->orientation = orientation;
  if ( !orientation )
      table = gtk_table_new (1, segments, FALSE);
  else
      table = gtk_table_new (segments, 1, FALSE);
  gtk_container_add (GTK_CONTAINER (led_bar), table);
  gtk_widget_show (table);
  half = .50 * segments;
  full = .75 * segments;
  gdk_color_parse ("#00F100", &active);
  gdk_color_parse ("#008C00", &inactive);
  for (i = 0; i < segments; i++)
    {
      if (i >= half && i <= full)
	{
	  gdk_color_parse ("#F1EE00", &active);
	  gdk_color_parse ("#8CAA00", &inactive);
	}
      else
	if (i >= full)
	  {
	    gdk_color_parse ("#F10000", &active);
	    gdk_color_parse ("#8C0000", &inactive);
	  }
      led_bar->segments[i] = gtk_led_new ();
      gtk_led_set_colors (GTK_LED (led_bar->segments[i]), &active, &inactive);

      if ( !orientation )
	  gtk_table_attach (GTK_TABLE (table), led_bar->segments[i],
				     i, (i + 1), 0, 1, 0, 0, 0, 0);
      else
	  gtk_table_attach (GTK_TABLE (table), led_bar->segments[i],
				     0, 1, (segments - i - 1), (segments - i),
                                     0, 0, 0, 0 );
      gtk_widget_show (led_bar->segments[i]);
    }

  return GTK_WIDGET (led_bar);
}
