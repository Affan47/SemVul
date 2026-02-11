scanFiles() {
  if (cacheFile.empty()) {
    cerr << subst(_("%1 scan: Please specify a --cache file.\n"),
                  binaryName);
    exit_tryHelp();
  }

  JigdoCache cache(cacheFile, optCacheExpiry, readAmount, *optReporter);
  cache.setParams(blockLength, md5BlockLength);
  if (addLabels(cache)) return 3;
  while (true) {
    try { cache.readFilenames(fileNames); }
    catch (RecurseError e) { optReporter->error(e.message); continue; }
    break;
  }
  JigdoCache::iterator ci = cache.begin(), ce = cache.end();
  if (optScanWholeFile) {

    while (ci != ce) { ci->getMD5Sum(&cache); ++ci; }
  } else {

    while (ci != ce) { ci->getSums(&cache, 0); ++ci; }
  }
  return 0;

}
