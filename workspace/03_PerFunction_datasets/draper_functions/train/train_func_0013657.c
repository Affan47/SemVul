setBasePoint(const Coordinate& basePt)
{
  if ( ! areaBasePt.get() )
      areaBasePt.reset( new Coordinate(basePt) );
}
