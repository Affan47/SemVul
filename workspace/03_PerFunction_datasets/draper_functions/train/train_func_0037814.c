create_sprite(int width, int height, struct color *pcolor)
{
  struct sprite *sprite = fc_malloc(sizeof(*sprite));
  cairo_t *cr;

  fc_assert_ret_val(width > 0, NULL);
  fc_assert_ret_val(height > 0, NULL);
  fc_assert_ret_val(pcolor != NULL, NULL);

  sprite->surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
         width, height);

  cr = cairo_create(sprite->surface);
  gdk_cairo_set_source_rgba(cr, &pcolor->color);
  cairo_paint(cr);
  cairo_destroy(cr);

  return sprite;
}
