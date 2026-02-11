cylinder(Clip *clip, float *point)
{


  int dim = clip->dim;
  int i;
  float r2 = 0, dot = 0, dx, *s, *p, *c;

  for(i=dim, p=point, c=origin, s=clip->surf; --i >= 0; p++, s++, c++)
    dot += (*p - *c) * *s;

  for(i=dim, p=point, c=origin, s=clip->surf; --i >= 0; p++, s++, c++) {
    dx = (*p - *c) - dot * *s;
    r2 += dx * dx;
  }
  return r2;
}
