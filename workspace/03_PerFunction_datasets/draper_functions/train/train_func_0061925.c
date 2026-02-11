GetAspect(planet1, planet2, ret1, ret2, i, j)
real *planet1, *planet2, *ret1, *ret2;
int i, j;
{
  int k;
  real l, m;

  grid->v[i][j] = grid->n[i][j] = 0;
  l = MinDistance(planet2[i], planet1[j]);
  for (k = us.nAsp; k >= 1; k--) {
    if (!FAcceptAspect(i, k, j))
      continue;
    m = l-rAspAngle[k];
    if (RAbs(m) < GetOrb(i, j, k)) {
      grid->n[i][j] = k;


      if (us.fAppSep)
        m = RSgn2(ret1[j]-ret2[i])*
          RSgn2(MinDifference(planet2[i], planet1[j]))*RSgn2(m)*RAbs(m);
      grid->v[i][j] = (int)(m*60.0);
    }
  }
}
