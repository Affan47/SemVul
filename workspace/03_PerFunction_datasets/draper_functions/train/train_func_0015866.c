handleSources(ArArgumentBuilder *arg)
{

  std::list<std::string> scanTypeList;

  for (size_t i = 0; i < arg->getArgc(); i++) {
    ArLog::log(ArLog::Normal,
               "ArMapSimple::handleSources() source #%i = %s",
               i, arg->getArg(i));
    scanTypeList.push_back(arg->getArg(i));
  }

  if (scanTypeList.empty()) {
    ArLog::log(ArLog::Terse,
              "ArMapSimple::handleSources() at least one source must be specified");
    return false;
  }

  remScansFromParser(true);

  createScans(scanTypeList);

  addScansToParser();

  return true;

}
