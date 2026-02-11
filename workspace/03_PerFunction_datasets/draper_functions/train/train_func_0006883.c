cmpxy_gt(const void *s1, const void *s2)
{
  int cmp = 0;
  xyinfo_t *xy1 = (xyinfo_t *) s1;
  xyinfo_t *xy2 = (xyinfo_t *) s2;

  if      ( xy1->y > xy2->y || (!(fabs(xy1->y - xy2->y) > 0) && xy1->x < xy2->x) ) cmp = -1;
  else if ( xy1->y < xy2->y || (!(fabs(xy1->y - xy2->y) > 0) && xy1->x > xy2->x) ) cmp =  1;

  return (cmp);
}
