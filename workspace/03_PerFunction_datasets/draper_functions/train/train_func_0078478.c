add_face (GtsSurface * s, GtsEdge ** e1, GtsEdge ** e2,
		      guint ne)
{
  guint i;

  for (i = 0; i < ne; i++) {
    GtsVertex * v1 = GTS_SEGMENT (e1[i])->v1;
    GtsVertex * v2 = GTS_SEGMENT (e2[i])->v1;
    GtsVertex * v3 = GTS_SEGMENT (e2[i])->v2;
    GtsVertex * v4 = GTS_SEGMENT (e1[i])->v2;
    GtsEdge * e3 = gts_edge_new (s->edge_class, v1, v3);
    GtsEdge * e4 = GTS_EDGE (gts_vertices_are_connected (v1, v2));
    GtsEdge * e5 = GTS_EDGE (gts_vertices_are_connected (v3, v4));

    if (e4 == NULL)
      e4 = gts_edge_new (s->edge_class, v1, v2);
    if (e5 == NULL)
      e5 = gts_edge_new (s->edge_class, v3, v4);

    gts_surface_add_face (s, gts_face_new (s->face_class, e4, e2[i], e3));
    gts_surface_add_face (s, gts_face_new (s->face_class, e3, e5, e1[i]));
  }
}
