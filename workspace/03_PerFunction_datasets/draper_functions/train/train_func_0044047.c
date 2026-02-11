clutter_cairo_texture_create_region_internal (ClutterCairoTexture *self,
                                              gint                 x_offset,
                                              gint                 y_offset,
                                              gint                 width,
                                              gint                 height)
{
  ClutterCairoTexturePrivate *priv = self->priv;
  cairo_rectangle_int_t region, area, inter;
  cairo_surface_t *surface;
  DrawContext *ctxt;
  cairo_t *cr;

  if (width < 0)
    width = priv->surface_width;

  if (height < 0)
    height = priv->surface_height;

  if (width == 0 || height == 0)
    {
      g_warning ("Unable to create a context for an image surface of "
                 "width %d and height %d. Set the surface size to be "
                 "at least 1 pixel by 1 pixel.",
                 width, height);
      return NULL;
    }

  surface = get_surface (self);

  ctxt = draw_context_create (self);

  region.x = x_offset;
  region.y = y_offset;
  region.width = width;
  region.height = height;

  area.x = 0;
  area.y = 0;
  area.width = priv->surface_width;
  area.height = priv->surface_height;


  intersect_rectangles (&area, &region, &inter);

  ctxt->rect = inter;

  cr = cairo_create (surface);
  cairo_set_user_data (cr, &clutter_cairo_texture_context_key,
		       ctxt,
                       clutter_cairo_texture_context_destroy);

  return cr;
}
