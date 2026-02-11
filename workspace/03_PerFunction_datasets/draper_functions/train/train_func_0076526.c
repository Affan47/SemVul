bounded(p)
     Point3 *p;
{
  if (! Pt3Equal(p,&Pt3Origin)) {
    if (p->x < MAXCLINE && p->y < MAXCLINE && p->z < MAXCLINE)
      return 1;
  }
  return 0;
}
