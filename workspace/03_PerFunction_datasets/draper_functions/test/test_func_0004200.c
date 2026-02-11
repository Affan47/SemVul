updateCache()
{
  if (currentValuesValid) return;
  OFString aString;
  imageDisplayFormat.getOFStringArray(aString,OFTrue);
  if (aString.substr(0,9) == "STANDARD\\")
  {
    unsigned long columns=0;
    unsigned long rows=0;
    const char *format = aString.c_str() + 9;

    if (2==sscanf(format, "%lu,%lu", &columns, &rows))
    {
      currentNumCols = columns;
      currentNumRows = rows;
      if ((columns > 0)&&(rows > 0)) currentValuesValid = OFTrue;
    } else {
      DCMPSTAT_INFO("cannot parse image display format '" << aString.c_str() << "'");
    }
  } else {
    DCMPSTAT_INFO("unknown image display format '" << aString.c_str() << "'");
  }
  return;
}
