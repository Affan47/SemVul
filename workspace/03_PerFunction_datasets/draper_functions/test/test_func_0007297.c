gpi_read_string(const char* field)
{
  int l1;
  char* res = NULL;

  l1 = gbfgetint16(fin);
  if (l1 > 0) {
    short l2;
    char first;

    first = gbfgetc(fin);
    if (first == 0) {
      char en[2];

      is_fatal((gbfgetc(fin) != 0),
               MYNAME ": Error reading field '%s'!", field);

      gbfread(en, 1, sizeof(en), fin);
      l2 = gbfgetint16(fin);
      is_fatal((l2 + 4 != l1),
               MYNAME ": Error out of sync (wrong size %d/%d) on field '%s'!", l1, l2, field);

      if ((en[0] < 'A') || (en[0] > 'Z') || (en[1] < 'A') || (en[1] > 'Z')) {
        fatal(MYNAME ": Invalid country code!\n");
      }
      res = (char*) xmalloc(l2 + 1);
      res[l2] = '\0';
      PP;
      if (l2 > 0) {
        gbfread(res, 1, l2, fin);
      }
    } else {
      res = (char*) xmalloc(l1 + 1);
      *res = first;
      *(res + l1) = '\0';
      PP;
      l1--;
      if (l1 > 0) {
        gbfread(res + 1, 1, l1, fin);
      }

    }
  }
#ifdef GPI_DBG
  dbginfo("%s: %s\n", field, (res == NULL) ? "<NULL>" : res);
#endif
  return res;
}
