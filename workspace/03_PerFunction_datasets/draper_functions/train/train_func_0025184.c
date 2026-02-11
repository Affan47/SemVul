variable_color (GtsObject * o)
{
  GfsDomain * domain = color_data[0];
  GfsVariable * v = color_data[1];
  Colormap * colormap = color_data[2];
  gdouble * min = color_data[3];
  gdouble * max = color_data[4];
  FttCell * cell;

  GtsPoint * p = GTS_POINT (o);
  FttVector pos;
  gdouble val;
  GtsColor c;

  pos.x = p->x;
  pos.y = p->y;
  pos.z = p->z;

  cell = gfs_domain_locate (domain, pos, -1, NULL);
  if (cell) {
    val = gfs_interpolate (cell, pos, v);
    c = colormap_color (colormap, (val - *min)/(*max - *min));
  }
  else
    c.r = c.g = c.b = 1.;
  return c;
}
