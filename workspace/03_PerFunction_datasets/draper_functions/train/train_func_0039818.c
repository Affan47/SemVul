setFilterCumulativeCleanDist(double dist)
{
  if (dist >= 0)
  {
    myFilterCumulativeCleanDist = dist;
    myFilterSquaredCumulativeCleanDist = dist * dist;
  }
  else
    ArLog::log(ArLog::Terse, "ArSick::setFilterCumulativeCleanDistDist given a distance less than 0.\n");
}
