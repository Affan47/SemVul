docrit(v)
vari *v;
{ double df, al;
  INT i;
  df = 0; al = 0.05;
  i = getarg(v,"df",1); if (i>0) sscanf(argval(v,i),"%lf",&df);
  i = getarg(v,"al",1); if (i>0) sscanf(argval(v,i),"%lf",&al);
  return(critval(lf.kap,lf.nk,lf.mi[MDIM],al,10,2,df));
}
