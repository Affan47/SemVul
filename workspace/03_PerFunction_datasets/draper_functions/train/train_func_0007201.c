mif_outputBoundaryPoints(ostream& out)
{
  int i, index;

  Point3 p;
  bool only_active = true;


  int mesh_index = model->getCurrentMeshIndex();

  int bp_count;
  BoundaryPoint** bp_points;


  index = 0;
  while (true) {
    BodyElement* be = model->getBoundary(index++);
    if (be==NULL) break;

    bp_count = 0;
    bp_points = NULL;

    be->getBoundaryPoints(bp_count, bp_points);

    for (i = 0; i < bp_count; i++) {

      BoundaryPoint* bp = bp_points[i];


      if ( bp->isVertex() ) {
        continue;
      }

      bp->checked = false;
    }

    delete[] bp_points;
    bp_points = NULL;
  }


  index = 0;
  while (true) {
    BodyElement* be = model->getBoundary(index++, only_active);
    if (be==NULL) break;

    bp_count = 0;
    bp_points = NULL;

    be->getBoundaryPoints(bp_count, bp_points);

    for (i= 0; i < bp_count; i++) {

      BoundaryPoint* bp = bp_points[i];

      if ( !bp->activeInMeshing ||
           bp->isVertex()       ||
           bp->checked
         ) {
        continue;
      }

      bp->point->getPoint(p);

      bp->checked = true;

      out << "NodeId: " << bp->tag << " -1";
      if ( bp->meshDensityType != ' ' ) {
        out << "  " << bp->meshDensityType << ": " << bp->meshDensityValue;
      }


      out << "  " << p[0] << " " << p[1];
      out << endl;
    }

    delete[] bp_points;
    bp_points = NULL;
  }

  return out;
}
