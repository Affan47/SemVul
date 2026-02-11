isCrossed(double ax, double ay, double bx, double by,
          double cx, double cy, double dx, double dy)
{


  double determinant, b1, b2;

  bx -= ax;
  by -= ay;
  cx -= ax;
  cy -= ay;
  dx -= ax;
  dy -= ay;

  determinant = dx*cy - dy*cx;

  if (determinant == 0.)
    return false;

  b1 = (cy*bx - cx*by)/determinant;
  if (b1 <= 0.)
    return false;

  b2 = (dx*by - dy*bx)/determinant;
  if (b2 <= 0.)
    return false;

  if (b1+b2 <= 1.)
    return false;

  return true;
}
