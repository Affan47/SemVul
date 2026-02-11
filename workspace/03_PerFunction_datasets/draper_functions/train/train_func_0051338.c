DBFCreateEx(const char *pszFilename, const char *pszCodePage) {
  DBFHandle psDBF;
  FILE* fp;
  char *pszFullname, *pszBasename;
  int i, ldid = -1;
  char chZero = '\0';


  pszBasename = (char *) malloc(strlen(pszFilename) + 5);
  strcpy(pszBasename, pszFilename);
  for (i = strlen(pszBasename) - 1; i > 0 && pszBasename[i] != '.' && pszBasename[i] != '/'
         && pszBasename[i] != '\\'; i--) { }
  if (pszBasename[i] == '.')
    pszBasename[i] = '\0';
  pszFullname = (char *) malloc(strlen(pszBasename) + 5);
  sprintf(pszFullname, "%s.dbf", pszBasename);


  fp = fopen(pszFullname, "wb");
  if (fp == NULL)
    return (NULL);
  fwrite(&chZero, 1, 1, fp);
  fclose(fp);

  fp = fopen(pszFullname, "rb+");
  if (fp == NULL)
    return (NULL);

  sprintf(pszFullname, "%s.cpg", pszBasename);
  if (pszCodePage != NULL) {
    if (strncmp(pszCodePage, "LDID/", 5) == 0) {
      ldid = atoi(pszCodePage + 5);
      if (ldid > 255)
        ldid = -1;
    }
    if (ldid < 0) {
      FILE* fpCPG = fopen(pszFullname, "w");
      fwrite((char *) pszCodePage, strlen(pszCodePage), 1, fpCPG);
      fclose(fpCPG);
    }
  }
  if (pszCodePage == NULL || ldid >= 0)
    remove(pszFullname);
  free(pszBasename);
  free(pszFullname);


  psDBF = (DBFHandle) calloc(1, sizeof(DBFInfo));
  psDBF->fp = fp;
  psDBF->nRecords = 0;
  psDBF->nFields = 0;
  psDBF->nRecordLength = 1;
  psDBF->nHeaderLength = 33;
  psDBF->panFieldOffset = NULL;
  psDBF->panFieldSize = NULL;
  psDBF->panFieldDecimals = NULL;
  psDBF->pachFieldType = NULL;
  psDBF->pszHeader = NULL;
  psDBF->nCurrentRecord = -1;
  psDBF->bCurrentRecordModified = FALSE;
  psDBF->pszCurrentRecord = NULL;
  psDBF->bNoHeader = TRUE;
  psDBF->iLanguageDriver = ldid > 0 ? ldid : 0;
  psDBF->pszCodePage = NULL;
  if (pszCodePage) {
    psDBF->pszCodePage = (char *) malloc(strlen(pszCodePage) + 1);
    strcpy(psDBF->pszCodePage, pszCodePage);
  }
  return (psDBF);
}
