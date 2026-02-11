getSegGen(double dist)
{
  std::auto_ptr<OffsetSegmentGenerator> osg(
    new OffsetSegmentGenerator(precisionModel, bufParams, dist)
  );
  return osg;
}

}
