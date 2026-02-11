loadWithErrorReport(const char *fname)
{
  int reason;
  Document *doc = load(fname, reason);
  if (doc)
    return doc;

  fprintf(stderr, "Could not read Ipe file '%s'\n", fname);
  switch (reason) {
  case Document::EVersionTooOld:
    fprintf(stderr, "The Ipe version of this document is too old.\n"
	    "Please convert it using 'ipe6upgrade'.\n");
    break;
  case Document::EVersionTooRecent:
    fprintf(stderr, "The document was created by a newer version of Ipe.\n"
	    "Please upgrade your Ipe installation.\n");
    break;
  case Document::EFileOpenError:
    perror("Error opening the file");
    break;
  default:
    fprintf(stderr, "Error parsing the document at position %d\n.", reason);
    break;
  }
  return 0;
}
