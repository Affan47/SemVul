create(int nof_points, Point3** points, ecif_EdgeGeometry_X* params,
                 enum linDeltaType lin_delta_type, double lin_delta, bool do_linearize)
{
  bool center_given = false;
  bool radius_given = false;

  Point3 p1, p2;


  if ( nof_points == 2 ) {
    data.start = new GcPoint(points[0]);
    data.end = new GcPoint(points[1]);

    data.start->getPoint(p1);
    data.end->getPoint(p2);

    if ( isZero(dist3(p1, p2)) ) {
      data.isClosed = true;
    } else {
      data.isClosed = false;
    }


  } else {
    data.isClosed = true;
    if ( params->start != NULL ) {
      data.start = new GcPoint(params->start);
    }
    if ( params->end != NULL ) {
      data.end = new GcPoint(params->end);
    }
    data.start_u = 0.0;
    data.end_u = TWO_PI;
  }


  if (params->location != NULL) {
    data.centerGiven = true;
    copy3(*params->location, data.center);
  }


  if (params->radius1 > 0 ) {
    data.radiusGiven = true;
    data.radius = params->radius1;
  }


  data.nofDefiningPoints = params->nofDefiningPoints;
  if ( data.nofDefiningPoints  > 0 ) {
    data.definingPoints = new Point3[data.nofDefiningPoints];
    for (int i = 0; i < data.nofDefiningPoints; i++) {
      for (int j = 0; j < 3; j++) {
        data.definingPoints[i][j] = params->definingPoints[i][j];
      }
    }
  }

  data.deltaType = lin_delta_type;
  data.delta = lin_delta;


  if ( !updateData() ) return false;

  setDeltaU(lin_delta_type, lin_delta);

  nofBoundaryPoints = 0;
  boundaryPoints = NULL;

  return true;
}
