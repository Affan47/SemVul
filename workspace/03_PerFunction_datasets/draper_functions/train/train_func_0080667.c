verifyCompilerVersion(AFILE saveFile) {
  char savedVersion[4];

  fread((void *)&savedVersion, sizeof(Aword), 1, saveFile);
  if (!ignoreErrorOption && strncmp(savedVersion, header->version, 4))
    error(M_SAVEVERS);
}
