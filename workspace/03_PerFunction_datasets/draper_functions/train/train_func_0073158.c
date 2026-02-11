d_def_18_(fortint * outputArray, unsigned char * gribSection1) {


int loop, N;
unsigned char fourBlanks[5] = "    ";
fortint * n = outputArray;
unsigned char * p = gribSection1;

  decodeMarsPart(n,p);
  p += 9;
  n += 5;

  *n++ = ONEBYTEINT(p);p++;
  *n++ = ONEBYTEINT(p);p++;
  *n++ = ONEBYTEINT(p);p++;

  *n++ = FOURBYTEINT(p);
  p += 4;

  *n++ = ONEBYTEINT(p);p++;
  N = *(n-1);

  p += 3;

  for( loop = 0; loop < N; loop++) {
    *n++ = FOURBYTEINT(p);
    p += 4;
  }


  for( loop = 0; loop < (15-N); loop++)
    *n++ = FOURBYTEINT(fourBlanks);

  return (fortint) (n - outputArray);
}
