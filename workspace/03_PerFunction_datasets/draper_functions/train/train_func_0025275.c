attachPointsToPointSets()
{
  axesPointSet.attachPointsToPointSet();
  scalePointSet.attachPointsToPointSet();

  PointSetListIterator itr;

  for (itr = curveList.begin(); itr != curveList.end(); ++itr)
    (*itr).attachPointsToPointSet();

  for (itr = measureList.begin(); itr != measureList.end(); ++itr)
    (*itr).attachPointsToPointSet();
}
