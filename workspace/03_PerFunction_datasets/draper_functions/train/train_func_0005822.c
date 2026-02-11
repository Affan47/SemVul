read_line(Char *c_addr, UCell u1, Cell wfileid)
{
  UCell u2, u3;
  Cell flag, wior;
  Cell c;
  struct Cellquad r;

  flag=-1;
  u3=0;
  for(u2=0; u2<u1; u2++) {
    c = getc((FILE *)wfileid);
    u3++;
    if (c=='\n') break;
    if (c=='\r') {
      if ((c = getc((FILE *)wfileid))!='\n')
	ungetc(c,(FILE *)wfileid);
      else
	u3++;
      break;
    }
    if (c==EOF) {
      flag=FLAG(u2!=0);
      break;
    }
    c_addr[u2] = (Char)c;
  }
  wior=FILEIO(ferror((FILE *)wfileid));
  r.n1 = u2;
  r.n2 = flag;
  r.n3 = u3;
  r.n4 = wior;
  return r;
}
