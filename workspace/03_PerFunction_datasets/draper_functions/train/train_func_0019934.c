SplicePossibleUser(int *idstart,int *idend,int *sh_end,int *lg_end,
		       int *argb,int *arge,int *argc,int idcheck,
		       int *id,int cmtmode)
{
  int match,k,pos;

  if (!matchStartSequence(S->User.mStart,idstart)) return 0;
  *idend=identifierEnd(*idstart);
  if ((*idend)&&!getChar(*idend-1)) return 0;


  *sh_end=*idend;
  if (!matchEndSequence(S->User.mEnd,sh_end)) *sh_end=-1;
  pos=*idend;
  match=matchSequence(S->User.mArgS,&pos);

  if (idcheck) {
    *id=findIdent(C->buf+*idstart,*idend-*idstart);
    if (*id<0) match=0;
  }
  *lg_end=-1;

  if (match) {
    *argc=0;
    while (1) {
      if (*argc>=MAXARGS) bug("too many macro parameters");
      argb[*argc]=pos;
      k=0;
      while(1) {
        pos=iterIdentifierEnd(pos);
        SkipPossibleComments(&pos,cmtmode,0);
        if (getChar(pos)==0) return (*sh_end>=0);
        if (strchr(S->User.stackchar,getChar(pos))) k++;
        if (k) { if (strchr(S->User.unstackchar,getChar(pos))) k--; }
        else {
          arge[*argc]=pos;
          if (matchSequence(S->User.mArgSep,&pos)) { match=0; break; }
          if (matchEndSequence(S->User.mArgE,&pos))
            { match=1; break; }
        }
        pos++;
      }
      (*argc)++;
      if (match) {
        *lg_end=pos;
        break;
      }
    }
  }
  return ((*lg_end>=0)||(*sh_end>=0));
}
