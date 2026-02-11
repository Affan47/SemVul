gdl_get_margins_from_pointer (GladeDesignLayout *layout, GtkWidget *widget, gint x, gint y)
{
  GladeDesignLayoutPrivate *priv = GLADE_DESIGN_LAYOUT_PRIVATE (layout);
  gint width, height, xx, yy, top, bottom, left, right;
  GdkRectangle rec, child_rec;
  Margins margin = 0;

  width = gtk_widget_get_allocated_width (widget);
  height = gtk_widget_get_allocated_height (widget);

  gtk_widget_translate_coordinates (widget, GTK_WIDGET (layout), 0, 0, &xx, &yy);

  top = gtk_widget_get_margin_top (widget);
  bottom = gtk_widget_get_margin_bottom (widget);
  left = gtk_widget_get_margin_left (widget);
  right = gtk_widget_get_margin_right (widget);

  rec.x = xx - left - OUTLINE_WIDTH;
  rec.y = yy - top - OUTLINE_WIDTH;
  rec.width = width + left + right + (OUTLINE_WIDTH * 2);
  rec.height = height + top + bottom + (OUTLINE_WIDTH * 2);

  gtk_widget_get_allocation (gtk_bin_get_child (GTK_BIN (layout)), &child_rec);
  child_rec.x = (child_rec.x + priv->child_offset) - OUTLINE_WIDTH;
  child_rec.y = (child_rec.y + priv->child_offset) - OUTLINE_WIDTH;
  child_rec.width += OUTLINE_WIDTH * 2;
  child_rec.height += OUTLINE_WIDTH * 2;

  gdk_rectangle_intersect (&rec, &child_rec, &rec);

  if (RECTANGLE_POINT_IN (rec, x, y))
    {
      if (y <= yy + OUTLINE_WIDTH) margin |= MARGIN_TOP;
      else if (y >= yy + height - OUTLINE_WIDTH) margin |= MARGIN_BOTTOM;

      if (x <= xx + OUTLINE_WIDTH) margin |= MARGIN_LEFT;
      else if (x >= xx + width - OUTLINE_WIDTH) margin |= MARGIN_RIGHT;
    }

  return margin;
}
