qh_initialvertices(int dim, setT *maxpoints, pointT *points, int numpoints) {
  pointT *point, **pointp;
  setT *vertices, *simplex;
  realT randr;
  int index, point_i, point_n;

  vertices= qh_settemp (dim + 1);
  simplex= qh_settemp (dim+1);
  if (qh ALLpoints)
    qh_maxsimplex (dim, NULL, points, numpoints, &simplex);
  else if (qh RANDOMoutside) {
    while (qh_setsize (simplex) != dim+1) {
      randr= qh_RANDOMint;
      randr= randr/(qh_RANDOMmax+1.0);
      index= (int)floor(qh num_points * randr);
      point= qh_point (index);
      qh_setunique (&simplex, point);
    }
  }else if (qh hull_dim >= 8) {
    qh_setunique (&simplex, SETfirst_(maxpoints));
    FOREACHpoint_i_(maxpoints) {
      if (point_i & 0x1) {
        qh_setunique (&simplex, point);
        if (qh_setsize (simplex) == dim)
	  break;
      }
    }
    if (qh_setsize (simplex) != dim) {
      while ((point= (pointT *)qh_setdellast (maxpoints))) {
        qh_setunique (&simplex, point);
        if (qh_setsize (simplex) == dim)
	  break;
      }
    }
    index= 0;
    while (qh_setsize (simplex) != dim) {
      point= qh_point (index++);
      qh_setunique (&simplex, point);
    }
    qh_maxsimplex (dim, maxpoints, points, numpoints, &simplex);
  }else
    qh_maxsimplex (dim, maxpoints, points, numpoints, &simplex);
  FOREACHpoint_(simplex)
    qh_setaddnth (&vertices, 0, qh_newvertex(point));
  qh_settempfree (&simplex);
  return vertices;
}
