psDrawPatch(x,y,c1,c2)
INT *x, *y, c1, c2;
{ fprintf(psfile,"/Q { %d %d %d %d %d %d %d %d } bind def\n",
    x[0],height-y[0], x[1],height-y[1],
    x[2],height-y[2], x[3],height-y[3]);
  psSetColor(c1);
  fprintf(psfile,"PF\n");
  if (c1==c2) return;
  psSetColor(c2);
  fprintf(psfile,"PB\n");
}
