holidayDateList(const MSResourceCode& resourceCode_)
{
  MSHolidaySet::Cursor c(holidaySet());
  MSGUARD(holidaySetMutex);

  if (holidaySet().locateElementWithKey(resourceCode_,c)==MSTrue)
    {
      return MSResourceHolidaySet(c.element());
    }
  else
    {
      return MSResourceHolidaySet("");
    }
}
