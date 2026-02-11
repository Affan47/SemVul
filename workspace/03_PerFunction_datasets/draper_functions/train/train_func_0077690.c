noparcomp(lf)
lfit *lf;
{ INT tg;
  if (lf->mi[MDEG0]<lf->mi[MDEG]) return(1);
  if (lf->mi[MUBAS]) return(1);
  tg = lf->mi[MTG] & 63;
  if (tg<=THAZ) return(1);
  if (tg==TROBT) return(1);
  if (tg==TCAUC) return(1);
  return(0);
}
