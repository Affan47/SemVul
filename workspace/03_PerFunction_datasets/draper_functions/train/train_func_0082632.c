StrCmpOptionNameIgnoreCase(const char *A, const char *B) {
  const char *X = A, *Y = B;
  char a = tolower(*A), b = tolower(*B);
  while (a == b) {
    if (a == '\0')
      return 0;

    a = tolower(*++X);
    b = tolower(*++Y);
  }

  if (a == '\0')
    return 1;
  if (b == '\0')
    return -1;


  return (a < b) ? -1 : 1;
}
