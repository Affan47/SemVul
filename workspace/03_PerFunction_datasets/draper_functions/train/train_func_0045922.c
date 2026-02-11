compare(const sccs_date& d) const
{
  int diff;

  if ( (diff = year - d.year) != 0 )
    return diff;
  else if ( (diff = yearday - d.yearday) != 0)
    return diff;
  else
    return daysecond - d.daysecond;
}
