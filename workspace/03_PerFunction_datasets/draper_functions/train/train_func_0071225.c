read_header(void)
{
  int len, i;
#ifdef GPI_DBG
  struct tm tm;
  char stime[32];
#endif

  i = gbfgetint32(fin);
  if (i != 0) {
    i = gbfgetint32(fin);
  }
  rdata->D2 = gbfgetint32(fin);

  gbfread(&rdata->S3, 1, sizeof(rdata->S3) - 1, fin);
  if (strncmp(rdata->S3, "GRMREC", 6) != 0) {
    fatal(MYNAME ": No GPI file!\n");
  }

  PP;
  rdata->crdate = gbfgetint32(fin);
#ifdef GPI_DBG
  tm = *localtime(&rdata->crdate);
  tm.tm_year += 20;
  tm.tm_mday -= 1;
  strftime(stime, sizeof(stime), "%Y/%m/%d %H:%M:%S", &tm);
  dbginfo("crdate = %lu (%s)\n", rdata->crdate, stime);
#endif

  (void) gbfgetint16(fin);

  len = gbfgetint16(fin);
  gbfseek(fin, len, SEEK_CUR);

  i =  gbfgetint32(fin);
  (void) gbfgetint32(fin);


  if (i == 15) {
    gbfseek(fin, 17, SEEK_CUR);
  }

  gbfread(&rdata->POI, 1, sizeof(rdata->POI) - 1, fin);
  if (strcmp(rdata->POI, "POI") != 0) {
    fatal(MYNAME ": Wrong or unsupported GPI file!\n");
  }

  for (i = 0; i < 3; i++) {
    (void)gbfgetc(fin);
  }
  gbfread(&rdata->S8, 1, sizeof(rdata->S8) - 1, fin);

  codepage = gbfgetint16(fin);
  (void) gbfgetint16(fin);


#ifdef GPI_DBG
  PP;
  dbginfo("< leaving header\n");
#endif
}
