edge_list (GtsMatrix * b, GtsPoint * o,
		       GSList * profile,
		       GtsSurface * s,
		       GtsEdge ** e, guint ne)
{
  guint i;
  GtsVertex * vold = NULL;
  GtsVertex * vfirst = NULL;
  gboolean colored = FALSE;
  GtsMatrix * c;

  if (GTS_IS_COLORED_VERTEX (o) &&
      gts_object_class_is_from_class (GTS_OBJECT_CLASS (s->vertex_class),
				      GTS_OBJECT_CLASS (gts_colored_vertex_class ())))
    colored = TRUE;
  if (GFS_IS_TWISTED_VERTEX (o)) {
    gdouble t = GFS_TWISTED_VERTEX (o)->theta;
    gdouble sint = sin (t), cost = cos (t);
    GtsMatrix * r = gts_matrix_new (cost, -sint, 0., 0.,
				    sint,  cost, 0., 0.,
				    0.,      0., 1., 0.,
				    0.,      0., 0., 0.);

    c = gts_matrix_product (b, r);
    gts_matrix_destroy (r);
  }
  else
    c = gts_matrix_new (b[0][0], b[0][1], b[0][2], 0.,
			b[1][0], b[1][1], b[1][2], 0.,
			b[2][0], b[2][1], b[2][2], 0.,
			0., 0., 0., 0.);

  for (i = 0; i <= ne && profile; i++, profile = profile->next) {
    GtsPoint * p = profile->data;
    GtsVertex * v = gts_vertex_new (s->vertex_class, p->x, p->y, 0.);

    if (colored)
      GTS_COLORED_VERTEX (v)->c = GTS_COLORED_VERTEX (o)->c;

    gts_point_transform (GTS_POINT (v), c);
    GTS_POINT (v)->x += o->x;
    GTS_POINT (v)->y += o->y;
    GTS_POINT (v)->z += o->z;

    if (vold != NULL)
      e[i-1] = gts_edge_new (s->edge_class, vold, v);
    vold = v;
    if (!vfirst) vfirst = v;
  }
  if (i <= ne && vold)
    e[i-1] = gts_edge_new (s->edge_class, vold, vfirst);
  gts_matrix_destroy (c);
}
