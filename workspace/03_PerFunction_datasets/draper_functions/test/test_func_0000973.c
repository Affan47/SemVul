focusblur_depth_map_get_depth (FblurDepthMap *depth_map,
                               gint           x,
                               gint           y)
{
  gsize offset;
  gint  depth;

  if (x >= depth_map->width)
    x %= depth_map->width;
  else if (x < 0)
    x = depth_map->width + (x % depth_map->width);

  if (y >= depth_map->height)
    y %= depth_map->height;
  else if (y < 0)
    y = depth_map->height + (y % depth_map->height);

  offset = y * depth_map->width + x;
  depth = depth_map->data[offset];

  return depth;
}
