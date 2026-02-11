gat2ch (struct dt *dtim, gaint tinc, char *ch, gaint chlen) {
gaint mn1,mn2,hr1,hr2,dy1,dy2,len,mnth;

  mnth = dtim->mo - 1L;
  mn1 = dtim->mn/10L;
  mn2 = dtim->mn - (mn1*10);
  hr1 = dtim->hr/10L;
  hr2 = dtim->hr - (hr1*10);
  dy1 = dtim->dy/10L;
  dy2 = dtim->dy - (dy1*10);
  if (tinc==1) {
    snprintf(ch,chlen-1,"%04i",dtim->yr);
  }
  else if (tinc==2) {
    if (dtim->yr==9999L) {
      snprintf(ch,chlen-1,"%s",monc[mnth]);
    } else {
      snprintf(ch,chlen-1,"%s%04i",monc[mnth],dtim->yr);
    }
  }
  else if (tinc==3) {
    snprintf(ch,chlen-1,"%i%i%s%04i",dy1,dy2,monc[mnth],dtim->yr);
  }
  else if (tinc==4) {
    snprintf(ch,chlen-1,"%i%iZ%i%i%s%04i",hr1,hr2,dy1,dy2,monc[mnth],dtim->yr);
  }
  else if (tinc==5) {
    snprintf(ch,chlen-1,"%i%i:%i%iZ%i%i%s%04i",hr1,hr2,mn1,mn2,dy1,dy2,monc[mnth],dtim->yr);
  }
  else snprintf(ch,chlen-1,"???");
  len=0;
  while (ch[len]) len++;
  return (len);
}
