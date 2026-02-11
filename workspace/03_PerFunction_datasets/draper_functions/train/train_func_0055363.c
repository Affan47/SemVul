gsrvar (struct gscmn *pcmn, char *name, char *oname) {
struct gsvar *var;
char rname[16],sname[16];
gaint len,pos,tpos,cnt,i;

  for (i=0; i<16; i++) rname[i] = ' ';
  pos = 0;
  len = 0;
  while (pos<16) {
    if (len>15) {
      if (*(name+pos)!=' ') {
        printf ("Compound variable name too long: ");
        for (i=0; i<16; i++) printf ("%c",*(name+i));
        return (1);
      }
      break;
    }
    rname[len] = *(name+pos);
    len++;
    if (*(name+pos)=='.') {
      pos++;
      cnt = 0;
      tpos = pos;
      for (i=0; i<16; i++) sname[i] = ' ';
      while (*(name+tpos)!='.' && *(name+tpos)!=' ' && tpos<16) {
        sname[cnt] = *(name+tpos);
        tpos++; cnt++;
      }
      if (cnt>0) {
        if (*sname=='_') var = pcmn->gvar;
        else var = pcmn->fvar;
        while (var) {
          for (i=0; i<16; i++) {
            if (*(sname+i) != var->name[i]) break;
          }
          if (i==16) break;
          var = var->forw;
        }
        if (var!=NULL) {
          cnt = 0;
          while (len<16 && *(var->strng+cnt)!='\0') {
            rname[len] = *(var->strng+cnt);
            cnt++; len++;
          }
          if (len==16 && *(var->strng+cnt)=='\0') {
            printf ("Compound variable name too long: ");
            for (i=0; i<16; i++) printf ("%c",*(name+i));
            return (1);
          }
          pos = tpos;
        }
      }
    } else pos++;
  }

  for (i=0; i<16; i++) *(oname+i) = rname[i];


  return (0);
}
