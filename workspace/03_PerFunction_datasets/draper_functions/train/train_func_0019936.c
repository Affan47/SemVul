fringe_x(fringe *f, double y)
{
  double dy, d;
  dy = f->c->y - y;
  d = sqrt(f->c->r * f->c->r - dy * dy);
  return f->side ? f->c->x + d : f->c->x - d;
  }
