d_def_8_(fortint * outputArray, unsigned char * gribSection1) {


int loop;
fortint * n = outputArray;
unsigned char * p = gribSection1;

  decodeMarsPart(n,p);
  p += 9;
  n += 5;

  *n++ = ONEBYTEINT(p);p++;

  for( loop = 0; loop < 12; loop++) {
     *n++ = ONEBYTEINT(p);
     p++;
  }

  return (fortint) (n - outputArray);
}
