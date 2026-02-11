filter_ro(
	const geom::CoordinateSequence& seq, size_t index)
{


    if (index == 0)
      return;

    const geom::Coordinate& p0 = seq.getAt(index - 1);
    const geom::Coordinate& p1 = seq.getAt(index);

    double delx = (p1.x - p0.x)/numSubSegs;
    double dely = (p1.y - p0.y)/numSubSegs;

    for (size_t i = 0; i < numSubSegs; ++i) {
      double x = p0.x + i*delx;
      double y = p0.y + i*dely;
      Coordinate pt(x, y);
      minPtDist.initialize();
      DistanceToPoint::computeDistance(geom, pt, minPtDist);
      maxPtDist.setMaximum(minPtDist);
    }

}
