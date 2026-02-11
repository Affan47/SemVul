createElement(int nof_vertices, int* vertex_ids, ecif_geometryType gt)
{
  if (nof_vertices < 3)
    return NULL;

  GcPoint** points = new GcPoint*[nof_vertices];

  for (int i = 0; i < nof_vertices; i++) {
    BodyElement* v = model->getVertexById(vertex_ids[i]);
    points[i] = (GcPoint*)v->getGeometry();
  }

  BodyElement* be = NULL;
  Geometry* gmtr = NULL;

  switch (nof_vertices) {


  case 3:
    break;


  case 4:


    switch (gt) {

    case ECIF_LINE:
      gmtr = new GcPlane(4, points);
      break;

    default:
      gmtr = new GcPlane(4, points);
      break;
    }

  default:
    break;
  }

  if ( gmtr != NULL )
    be = new BodyElement3D(nof_vertices, vertex_ids, gmtr);

  return be;
}
