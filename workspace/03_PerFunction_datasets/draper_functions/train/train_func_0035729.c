softstrpos(char *s, char *k)
{ char c,d;
  int i;
  d = upcasec(*k);
  while (c = *s)
   { if (upcasec(c) == d)
       { i = 0;
         do if (!k[++i]) return(s);
         while (upcasec(s[i]) == upcasec(k[i])); }
     s++; }
  return(NULL); }
