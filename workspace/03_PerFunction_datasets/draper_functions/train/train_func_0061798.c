addHoliday(const MSHoliday& aHoliday_)
{
  MSHolidaySet::Cursor c(holidaySet());
  MSGUARD(holidaySetMutex);

  if (_locateOrInstallHolidaySet(holidaySet(),aHoliday_.resourceCode(),c)==MSTrue)
    {
      MSResourceHolidaySet& aSet=holidaySet().elementAt(c);
      aSet.addOrReplaceElementWithKey(aHoliday_);
    }
  else
    {
      MSResourceHolidaySet aResourceHolidaySet(aHoliday_.resourceCode());
      aResourceHolidaySet.addOrReplaceElementWithKey(aHoliday_);
      holidaySet().add(aResourceHolidaySet);
    }

  return MSTrue;
}
