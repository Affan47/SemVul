bb_intersect(GtkAllocation *a, GtkAllocation *b)
{
  gint xmin, xmax, ymin, ymax;
  xmax = MIN(a->x+a->width,b->x+b->width);
  xmin = MAX(a->x,b->x);
  if(xmin > xmax) return FALSE;
  ymax = MIN(a->y+a->height,b->y+b->height);
  ymin = MAX(a->y,b->y);
  if(ymin > ymax) return FALSE;
  return TRUE;
}
