write_image_square (FttCell * cell, gpointer * data)
{
  Colormap * colormap = data[0];
  gdouble * min = data[1];
  gdouble * max = data[2];
  GfsVariable * v = data[3];
  Image * image = data[4];
  FttVector * lambda = data[5];
  FttVector p;
  GtsColor fc = { 0., 0., 0. };
  if (GFS_HAS_DATA (cell, v))
    fc = colormap_color (colormap, (GFS_VALUE (cell, v) - *min)/(*max - *min));
  Color c;
  gdouble size = ftt_cell_size (cell)/2.;
  FttVector p1, p2;

  ftt_cell_pos (cell, &p);
  c.r = fc.r*255;
  c.g = fc.g*255;
  c.b = fc.b*255;
  p1.x = (p.x - size)/lambda->x + 1e-9;
  p1.y = (p.y - size)/lambda->y + 1e-9;
  p2.x = (p.x + size)/lambda->x - 1e-9;
  p2.y = (p.y + size)/lambda->y - 1e-9;
  image_draw_square (image, &p1, &p2, c);
}
