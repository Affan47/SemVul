find_furthest_visible_point(CPoint &alpha,
        CPoint p0, CPoint p1)
{
  CPoint M;  Region Rp0, Rp1, Rm;

  if ( (Rp1 = FindRegion(p1)) == inside )  {
    alpha = p1;  return 1;
  }
  Rp0 = FindRegion(p0);
  while ( 1 )  {
    if ( Rp0 & Rp1 )  return 0;
    M.x = (p0.x+p1.x) >> 1;
    M.y = (p0.y+p1.y) >> 1;
    if ( M == p0 || M == p1 )  {
      if ( Rp1 == inside )  {
        alpha = p1; return 1;
      }
      else if ( Rp0 == inside )  {
        alpha = p0; return 1;
      }
      else  return 0;
      break;
    }
    Rm = FindRegion(M);
    if ( Rm & Rp1 )  { p1 = M;  Rp1 = Rm; }
    else  { p0 = M;  Rp0 = Rm; }
  }
  return 1;


}
