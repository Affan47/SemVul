scanEncodingDirs() {
  GDir *dir;
  GDirEntry *entry;
  const char *dataRoot = popplerDataDir ? popplerDataDir : POPPLER_DATADIR;


  size_t bufSize = strlen(dataRoot) + strlen("/nameToUnicode") + 1;
  char *dataPathBuffer = new char[bufSize];

  snprintf(dataPathBuffer, bufSize, "%s/nameToUnicode", dataRoot);
  dir = new GDir(dataPathBuffer, gTrue);
  while (entry = dir->getNextEntry(), entry != NULL) {
    if (!entry->isDir()) {
      parseNameToUnicode(entry->getFullPath());
    }
    delete entry;
  }
  delete dir;

  snprintf(dataPathBuffer, bufSize, "%s/cidToUnicode", dataRoot);
  dir = new GDir(dataPathBuffer, gFalse);
  while (entry = dir->getNextEntry(), entry != NULL) {
    addCIDToUnicode(entry->getName(), entry->getFullPath());
    delete entry;
  }
  delete dir;

  snprintf(dataPathBuffer, bufSize, "%s/unicodeMap", dataRoot);
  dir = new GDir(dataPathBuffer, gFalse);
  while (entry = dir->getNextEntry(), entry != NULL) {
    addUnicodeMap(entry->getName(), entry->getFullPath());
    delete entry;
  }
  delete dir;

  snprintf(dataPathBuffer, bufSize, "%s/cMap", dataRoot);
  dir = new GDir(dataPathBuffer, gFalse);
  while (entry = dir->getNextEntry(), entry != NULL) {
    addCMapDir(entry->getName(), entry->getFullPath());
    toUnicodeDirs->append(entry->getFullPath()->copy());
    delete entry;
  }
  delete dir;

  delete[] dataPathBuffer;
}
