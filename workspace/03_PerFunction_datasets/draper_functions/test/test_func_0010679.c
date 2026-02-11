remFromFileParser(ArFileParser *fileParser)
{
  if (myTypeToScanMap.empty()) {
    return false;
  }
  bool isRemoved = true;

  for (ArTypeToScanMap::iterator iter = myTypeToScanMap.begin();
       iter != myTypeToScanMap.end(); iter++) {
    ArMapScan *mapScan = iter->second;
    if (mapScan != NULL) {
      isRemoved = mapScan->remFromFileParser(fileParser) && isRemoved;
    }
  }
  return isRemoved;
}
