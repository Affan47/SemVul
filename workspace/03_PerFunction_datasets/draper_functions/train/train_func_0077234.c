drl(key,dv,mi)
char *key;
INT *dv, *mi;
{ INT i, nd;
  nd = readilist(dv,key,0,mi[MDEG],0);
  for (i=0; i<nd; i++)
  { if ((dv[i]<1) | (dv[i]>mi[MDIM]))
      ERROR(("drl: Invalid derivatives %s",key));
    dv[i]--;
  }
  return(nd);
}
