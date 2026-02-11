expansion_sum(int elen, REAL *e, int flen, REAL *f, REAL *h)

{
  REAL Q;
  INEXACT REAL Qnew;
  int findex, hindex, hlast;
  REAL hnow;
  INEXACT REAL bvirt;
  REAL avirt, bround, around;

  Q = f[0];
  for (hindex = 0; hindex < elen; hindex++) {
    hnow = e[hindex];
    Two_Sum(Q, hnow, Qnew, h[hindex]);
    Q = Qnew;
  }
  h[hindex] = Q;
  hlast = hindex;
  for (findex = 1; findex < flen; findex++) {
    Q = f[findex];
    for (hindex = findex; hindex <= hlast; hindex++) {
      hnow = h[hindex];
      Two_Sum(Q, hnow, Qnew, h[hindex]);
      Q = Qnew;
    }
    h[++hlast] = Q;
  }
  return hlast + 1;
}
