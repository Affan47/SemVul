handleDataIntro(ArArgumentBuilder *arg)
{
  remScansFromParser(false);

  myMapSupplement->remFromFileParser(myLoadingParser);
  myMapInfo->remFromFileParser(myLoadingParser);
  myMapObjects->remFromFileParser(myLoadingParser);

  myInactiveInfo->remFromFileParser(myLoadingParser);
  myInactiveObjects->remFromFileParser(myLoadingParser);
  myChildObjects->remFromFileParser(myLoadingParser);

  myLoadingParser->remHandler("Sources:");


  myLoadingParser->remHandler((const char *)NULL);


  updateMapCategory();

  ArLog::log(ArLog::Verbose,
             "ArMapSimple::handleDataIntro %s",
             arg->getExtraString());


  if (arg->getExtraString() != NULL) {
    myLoadingDataTag = arg->getExtraString();
  }
  else {
    myLoadingDataTag = "";
  }


  bool isLineDataTag = false;

  if (myLoadingScan != NULL) {
    myLoadingScan->remExtraFromFileParser(myLoadingParser);
  }

  myLoadingScan = findScanWithDataKeyword(myLoadingDataTag.c_str(),
                                          &isLineDataTag);

  if (myLoadingScan != NULL) {
    myLoadingScan->addExtraToFileParser(myLoadingParser, isLineDataTag);
  }

  return false;

}
