UUScanHeader (FILE *datei, headers *envelope)
{
  char *ptr;

  while (!feof (datei)) {
    if ((ptr = ScanHeaderLine (datei, NULL)) == NULL)
      break;
    if (*ptr == '\0')
      break;
    ParseHeader (envelope, ptr);
  }
  return 0;
}
