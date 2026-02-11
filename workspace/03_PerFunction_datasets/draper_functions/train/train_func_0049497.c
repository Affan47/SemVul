readModuleStores(std::list<ModuleStore> &slist) {
  int okCounter=0;
  int errorCounter=0;
  bool rv;

  rv=readModuleStoresFrom("/usr/local/lib/cyberjack/firmware", slist);
  if (rv) okCounter++;
  else errorCounter++;
  rv=readModuleStoresFrom("/usr/lib/cyberjack/firmware", slist);
  if (rv) okCounter++;
  else errorCounter++;
  rv=readModuleStoresFrom("/lib/cyberjack/firmware", slist);
  if (rv) okCounter++;
  else errorCounter++;

  if (okCounter==0) {
    fprintf(stderr, "ERROR: Could not load any module store\n");
    return false;
  }
  return true;
}
