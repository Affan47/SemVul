getFaceVerticies(simplex *s, gint i, GwyDelaunayVertex **p1, GwyDelaunayVertex **p2,
                                         GwyDelaunayVertex **p3, GwyDelaunayVertex **p4  )
{
  switch (i)
  {
    case 0:
      *p1 = s->p[0];
      *p2 = s->p[1];
      *p3 = s->p[2];
      *p4 = s->p[3];
      break;
    case 1:
      *p1 = s->p[3];
      *p2 = s->p[1];
      *p3 = s->p[0];
      *p4 = s->p[2];
      break;
    case 2:
      *p1 = s->p[0];
      *p2 = s->p[2];
      *p3 = s->p[3];
      *p4 = s->p[1];
      break;
    case 3:
      *p1 = s->p[3];
      *p2 = s->p[2];
      *p3 = s->p[1];
      *p4 = s->p[0];
      break;
  }
}
