modifiedGeometryMeasure(QString name)
{
  PointSetListIterator itr;

  for (itr = measureList.begin(); itr != measureList.end(); ++itr)
    if (name == (*itr).name())
      return (*itr).modifiedGeometry();

  return false;
}
