isDelaunay(simplex *s, GwyDelaunayVertex *p)
{
  gdouble inSph;


  gdouble orientation = orient3dfast(s->p[0]->v,
                                    s->p[1]->v,
                                    s->p[2]->v,
                                    s->p[3]->v);


  if (orientation <= 0)
  {


    return -1;
  }


  inSph = inspherefast(  s->p[0]->v,
                                s->p[1]->v,
                                s->p[2]->v,
                                s->p[3]->v, p);


  if (inSph == 0) return -1;

  return inSph < 0;

}
