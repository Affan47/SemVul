search_backward( int startPos, const char *searchString,
                                     int *foundPos, int matchCase )
{
  if (!searchString) return 0;
  int bp;
  const char* sp;
  while (startPos > 0) {
    bp = startPos-1;
    sp = searchString+strlen(searchString)-1;
    do {
      if (sp < searchString) { *foundPos = bp+1; return 1; }
    } while ((matchCase ? character(bp--) == *sp-- :
                         toupper(character(bp--)) == toupper(*sp--))
             && bp >= 0);
    startPos--;
  }
  return 0;
}
