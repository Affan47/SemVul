BoundingBox(BoxRegion const & b1, BoxRegion const & b2 )
{
  BoxRegion r;
  unsigned int xmin = std::min( b1.GetXMin(), b2.GetXMin() );
  unsigned int xmax = std::min( b1.GetXMax(), b2.GetXMax() );
  unsigned int ymin = std::min( b1.GetYMin(), b2.GetYMin() );
  unsigned int ymax = std::min( b1.GetYMax(), b2.GetYMax() );
  unsigned int zmin = std::min( b1.GetZMin(), b2.GetZMin() );
  unsigned int zmax = std::min( b1.GetZMax(), b2.GetZMax() );

  r.SetDomain(xmin, xmax, ymin, ymax, zmin, zmax);
  return r;
}
