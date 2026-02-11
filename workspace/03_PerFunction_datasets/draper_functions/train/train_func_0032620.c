moveMeasureDown(QString name)
{
  PointSetListIterator itr;

  for (itr = measureList.begin(); itr != measureList.end(); ++itr)
    if (name == (*itr).name())
    {
      PointSet pointSet = (*itr);
      itr = measureList.remove(itr);
      ++itr;
      measureList.insert(itr, pointSet);
      return;
    }

  FATAL_ENGAUGE("unable to move measure down");
}
