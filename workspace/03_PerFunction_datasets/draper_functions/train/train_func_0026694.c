verifyGameId(AFILE saveFile) {
  Aword savedUid;

  fread((void *)&savedUid, sizeof(Aword), 1, saveFile);
  if (!ignoreErrorOption && savedUid != header->uid)
    error(M_SAVEVERS);
}
