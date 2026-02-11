bonobo_dock_band_insert (BonoboDockBand *band,
                        GtkWidget *child,
                        guint offset,
                        gint position)
{
  BonoboDockBandChild *band_child;

  DEBUG (("%08x", (unsigned int) band));

  if (BONOBO_IS_DOCK_ITEM (child)
      && !docking_allowed (band, BONOBO_DOCK_ITEM (child)))
    return FALSE;

  if (BONOBO_IS_DOCK_ITEM (child) &&
      !bonobo_dock_item_set_orientation (BONOBO_DOCK_ITEM (child),
					 band->orientation))
      return FALSE;

  if (position < 0 || position > (gint) band->num_children)
    position = band->num_children;

  band_child = g_new (BonoboDockBandChild, 1);
  band_child->widget = child;
  band_child->offset = offset;
  band_child->real_offset = 0;

  if (position == 0)
    band->children = g_list_prepend (band->children, band_child);
  else if ((guint) position == band->num_children)
    band->children = g_list_append (band->children, band_child);
  else
    {
      GList *p;

      p = g_list_nth (band->children, position);
      p = g_list_prepend (p, band_child);
    }

  gtk_widget_set_parent (child, GTK_WIDGET (band));

  if (GTK_WIDGET_REALIZED (child->parent))
    gtk_widget_realize (child);

  if (GTK_WIDGET_VISIBLE (child->parent) && GTK_WIDGET_VISIBLE (child))
    {
      if (GTK_WIDGET_MAPPED (child->parent))
	gtk_widget_map (child);

      gtk_widget_queue_resize (child);
    }

  band->num_children++;
  DEBUG (("now num_children = %d", band->num_children));

  return TRUE;
}
