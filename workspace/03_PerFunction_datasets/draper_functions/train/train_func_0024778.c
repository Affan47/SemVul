xcopy(char m[][MATY], int x, int y, char *s, int l)
{ int i;
  char c;
  i = 0;
  while (i < l)
   { if (x >= MATX) break;
     if (!(c = *s++)) break;
     m[x++][y] = c;
     i++; }}
