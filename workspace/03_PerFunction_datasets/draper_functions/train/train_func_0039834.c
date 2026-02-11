charset(n, controlfile)
int n;
ZFILE *controlfile;
{
  int ch;

  skipws(controlfile);
  if (Zgetc(controlfile) != '9') {
    skiptoeol(controlfile);
    return;
    }
  ch = Zgetc(controlfile);
  if (ch == '6') {
     gn[n] = 65536L * charsetname(controlfile) + 0x80;
     gndbl[n] = 0;
     skiptoeol(controlfile);
     return;
     }
  if (ch != '4') {
    skiptoeol(controlfile);
    return;
    }
  ch = Zgetc(controlfile);
  if (ch == 'x') {
     if (Zgetc(controlfile) != '9') {
       skiptoeol(controlfile);
       return;
       }
     if (Zgetc(controlfile) != '4') {
       skiptoeol(controlfile);
       return;
       }
     skipws(controlfile);
     gn[n] = 65536L * charsetname(controlfile);
     gndbl[n] = 1;
     skiptoeol(controlfile);
     return;
     }
  Zungetc(ch, controlfile);
  skipws(controlfile);
  gn[n] = 65536L * charsetname(controlfile);
  gndbl[n] = 0;
  return;
  }
