readfontchar(file,theord)
ZFILE *file;
inchr theord;
{
  int row,k;
  char templine[MAXLEN+1];
  outchr endchar, outline[MAXLEN+1];
  fcharnode *fclsave;

  fclsave = fcharlist;
  fcharlist = (fcharnode*)myalloc(sizeof(fcharnode));
  fcharlist->ord = theord;
  fcharlist->thechar = (outchr**)myalloc(sizeof(outchr*)*charheight);
  fcharlist->next = fclsave;

  for (row=0;row<charheight;row++) {
    if (myfgets(templine,MAXLEN,file)==NULL) {
      templine[0] = '\0';
      }
#ifdef TLF_FONTS
    utf8_to_wchar(templine,MAXLEN,outline,MAXLEN,0);
#else
    strcpy(outline,templine);
#endif
    k = STRLEN(outline)-1;
    while (k>=0 && ISSPACE(outline[k])) {
      k--;
      }
    if (k>=0) {
      endchar = outline[k];
      while (k>=0 && outline[k]==endchar) {
        k--;
        }
      }
    outline[k+1] = '\0';
    fcharlist->thechar[row] = (outchr*)myalloc(sizeof(outchr)*(STRLEN(outline)+1));
    STRCPY(fcharlist->thechar[row],outline);
    }
}
