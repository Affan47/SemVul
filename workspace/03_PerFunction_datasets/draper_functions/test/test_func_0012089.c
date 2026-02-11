showatrs(
  Aword atradr
)
#else
static void showatrs(atradr)
  Aword atradr;
#endif
{
  AtrElem *at;
  int i;
  char str[80];

  if (atradr == 0) return;

  i = 1;
  for (at = (AtrElem *) addrTo(atradr); !endOfTable(at); at++) {
    sprintf(str, "$i%3ld: %ld (%s)", (long) i, (unsigned long) at->val, (char *) addrTo(at->stradr));
#if ISO == 0
    fromIso(str, str);
#endif
    output(str);
    i++;
  }
}
