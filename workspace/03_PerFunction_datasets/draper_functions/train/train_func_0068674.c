na_tray_draw_icon (GtkWidget *widget,
		   gpointer   data)
{
  cairo_t *cr = (cairo_t *) data;

  if (na_tray_child_has_alpha (NA_TRAY_CHILD (widget)))
    {
      GtkAllocation allocation;

      gtk_widget_get_allocation (widget, &allocation);

      cairo_save (cr);
      gdk_cairo_set_source_window (cr,
                                   gtk_widget_get_window (widget),
				   allocation.x,
				   allocation.y);
      cairo_rectangle (cr, allocation.x, allocation.y, allocation.width, allocation.height);
      cairo_clip (cr);
      cairo_paint (cr);
      cairo_restore (cr);
    }
}
