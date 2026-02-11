e_def_16_(fortint * inputArray, unsigned char * gribSection1) {


int loop;
fortint * n = inputArray;
unsigned char * p = gribSection1;

  encodeMarsPart(n,p);
  p += 9;
  n += 5;

  MOVE2BYTES(p,n);
  p += 2;
  n++;

  n++;

  MOVE2BYTES(p,n);
  p += 2;
  n++;
  MOVE2BYTES(p,n);
  p += 2;
  n++;
  MOVE4BYTES(p,n);
  p += 4;
  n++;

  *p++ = ONEBYTE(n);n++;

  MOVE2BYTES(p,n);
  p += 2;
  n++;

  for( loop = 63; loop <= 80; loop++ )
    *p++ = (unsigned char) 0;

  return (fortint) (80);
}
