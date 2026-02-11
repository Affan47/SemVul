removeMeasure(QString name)
{
  PointSetListIterator itr;

  for (itr = measureList.begin(); itr != measureList.end(); ++itr)
    if (name == (*itr).name())
    {
      measureList.remove(itr);
      return;
    }

  FATAL_ENGAUGE("unable to remove measure");
}
