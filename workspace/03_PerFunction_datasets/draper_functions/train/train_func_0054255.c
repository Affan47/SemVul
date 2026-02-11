e_map_set_hadjustment_values (EMap *map)
{
  GtkAllocation  allocation;
  EMapPrivate *priv = map->priv;
  GtkAdjustment *adj = priv->hadjustment;
  gdouble old_value;
  gdouble new_value;
  gdouble new_upper;

  gtk_widget_get_allocation (GTK_WIDGET (map), &allocation);

  old_value = gtk_adjustment_get_value (adj);
  new_upper = MAX (allocation.width, gdk_pixbuf_get_width (priv->map_pixbuf));

  g_object_set (adj,
                "lower", 0.0,
                "upper", new_upper,
                "page-size", (gdouble)allocation.height,
                "step-increment", allocation.height * 0.1,
                "page-increment", allocation.height * 0.9,
                NULL);

  new_value = CLAMP (old_value, 0, new_upper - allocation.width);
  if (new_value != old_value)
    gtk_adjustment_set_value (adj, new_value);
}
