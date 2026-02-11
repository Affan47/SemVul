clear_exposed_input_region (FooScrollArea  *area,
                            cairo_region_t *exposed)
{
  int i;
  cairo_region_t *viewport;
  GdkRectangle allocation;

  gtk_widget_get_allocation (GTK_WIDGET (area), &allocation);
  allocation.x = 0;
  allocation.y = 0;
  allocation_to_canvas (area, &allocation.x, &allocation.y);

  viewport = cairo_region_create_rectangle (&allocation);
  cairo_region_subtract (viewport, exposed);

  for (i = 0; i < area->priv->input_regions->len; ++i)
    {
      InputRegion *region = area->priv->input_regions->pdata[i];

      cairo_region_intersect (region->region, viewport);

      if (cairo_region_is_empty (region->region))
        {
          input_region_free (region);
          g_ptr_array_remove_index_fast (area->priv->input_regions, i--);
        }
    }

  cairo_region_destroy (viewport);
}
