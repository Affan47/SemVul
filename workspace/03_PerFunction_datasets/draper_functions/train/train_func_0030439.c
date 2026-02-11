dradp(a, b, c, result, mult)
REAL *a, *b, *c, *result, mult;
{
  REAL vab[3], vbc[3], vca[3], Ar[3], tmp[3];
  REAL lab=0, lbc=0, lca=0, Area, rp, rr;
  int i;
  for ( i = 0 ; i < 3 ; i++ ) {
    vab[i] = b[i] - a[i]; lab += vab[i]*vab[i];
    vbc[i] = c[i] - b[i]; lbc += vbc[i]*vbc[i];
    vca[i] = a[i] - c[i]; lca += vca[i]*vca[i];
  }

  cross_prod(vca,vab,Ar); Area = SDIM_dot(Ar,Ar);

  rr = 4*Area/(lab*lbc*lca); if (rr==0.) return 0;
  ke_pow(rr,rp); rp *= mult;
  mult = -2*ke_power*rp; cross_prod(vbc,Ar,tmp);
  for ( i = 0 ; i < SDIM ; i++ )
    result[i] += mult*(vca[i]/lca - vab[i]/lab + tmp[i]/Area);
  return rp;
}
