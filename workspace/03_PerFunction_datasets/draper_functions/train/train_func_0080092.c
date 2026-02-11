isEndpoint(const Geometry& linearGeom) const
{
  const LineString& lineComp = dynamic_cast<const LineString&>(
      *(linearGeom.getGeometryN(componentIndex)) );

  unsigned int nseg = lineComp.getNumPoints() - 1;
  return segmentIndex >= nseg
        || (segmentIndex == nseg && segmentFraction >= 1.0);

}
