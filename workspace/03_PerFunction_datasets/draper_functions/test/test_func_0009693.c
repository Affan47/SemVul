quanfun(phen, thislocus, i, j, mean, LINK)
phenotype *phen;
locusvalues *thislocus;
int i, j;
double *mean;
struct LOC_getvect *LINK;
{
  double val;
  int it, jt, FORLIM, FORLIM1;

  val = 1.0;
  if (phen->missing)
    return val;
  val = 0.0;
  FORLIM = thislocus->UU.U1.ntrait;
  for (it = 0; it < FORLIM; it++) {
    FORLIM1 = thislocus->UU.U1.ntrait;
    for (jt = 0; jt < FORLIM1; jt++) {
      if (i == j)
	val += thislocus->UU.U1.vmat[it]
	       [jt] * (phen->x[jt] - mean[jt]) *
	       (phen->x[it] - mean[it]);
      else
	val += thislocus->UU.U1.conmat * thislocus->UU.U1.vmat[it]
	       [jt] * (phen->x[jt] - mean[jt]) *
	       (phen->x[it] - mean[it]);
    }
  }
  val = thislocus->UU.U1.det * exp(-val * 0.5);
  if (i != j)
    val *= thislocus->UU.U1.contrait;
  return val;
}
