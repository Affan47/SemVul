get_pixel_color(gfloat* in_buf,
                const GeglRectangle* rect,
                gint x,
                gint y)
{
  gint ix = x - rect->x;
  gint iy = y - rect->y;
  ix = CLAMP(ix, 0, rect->width-1);
  iy = CLAMP(iy, 0, rect->height-1);

  return &in_buf[(iy*rect->width + ix) * 4];
}
