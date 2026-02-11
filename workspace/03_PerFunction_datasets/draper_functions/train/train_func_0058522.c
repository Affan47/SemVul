dSolveL1_1 (const dReal *L, dReal *B, int n, int lskip1)
{

  dReal Z11,m11,Z21,m21,p1,q1,p2,*ex;
  const dReal *ell;
  int i,j;

  for (i=0; i < n; i+=2) {


    Z11=0;
    Z21=0;
    ell = L + i*lskip1;
    ex = B;

    for (j=i-2; j >= 0; j -= 2) {

      p1=ell[0];
      q1=ex[0];
      m11 = p1 * q1;
      p2=ell[lskip1];
      m21 = p2 * q1;
      Z11 += m11;
      Z21 += m21;

      p1=ell[1];
      q1=ex[1];
      m11 = p1 * q1;
      p2=ell[1+lskip1];
      m21 = p2 * q1;

      ell += 2;
      ex += 2;
      Z11 += m11;
      Z21 += m21;

    }

    j += 2;
    for (; j > 0; j--) {

      p1=ell[0];
      q1=ex[0];
      m11 = p1 * q1;
      p2=ell[lskip1];
      m21 = p2 * q1;

      ell += 1;
      ex += 1;
      Z11 += m11;
      Z21 += m21;
    }

    Z11 = ex[0] - Z11;
    ex[0] = Z11;
    p1 = ell[lskip1];
    Z21 = ex[1] - Z21 - p1*Z11;
    ex[1] = Z21;

  }
}
