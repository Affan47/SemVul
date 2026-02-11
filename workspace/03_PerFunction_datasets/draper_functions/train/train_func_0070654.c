addToFileParser(ArFileParser *fileParser)
{
  if (fileParser == NULL) {
    return false;
  }
  if (!fileParser->addHandler("OriginLatLongAlt:", &myOriginLatLongAltCB))
  {
    ArLog::log(ArLog::Terse,
               "ArMapSupplement::addToFileParser: could not add handlers");
    return false;
  }
  ArLog::log(ArLog::Verbose,
             "ArMapSupplement::addToFileParser() successfully added handlers");

  return true;

}
