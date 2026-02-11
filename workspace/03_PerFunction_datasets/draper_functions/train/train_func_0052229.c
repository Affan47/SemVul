c_ekkbtj4p_after_dense(const double * COIN_RESTRICT dluval,
				   const int * COIN_RESTRICT hrowi,
				   const int * COIN_RESTRICT mcstrt,
				   double * COIN_RESTRICT dwork1, int i,int jpiv)
{
  int iel;
  mcstrt -= jpiv;
  i += jpiv;
  iel=mcstrt[i+1];
  for (; i > jpiv+1; i-=2) {
    int i1 = mcstrt[i];
    double dv1 = dwork1[i];
    double dv2;
    for (; iel < i1; iel++) {
      int irow = hrowi[iel];
      dv1 += SHIFT_REF(dwork1, irow) * dluval[iel];
    }
    i1 = mcstrt[i-1];
    dv2 = dwork1[i-1];
    dwork1[i] = dv1;
    for (; iel < i1; iel++) {
      int irow = hrowi[iel];
      dv2 += SHIFT_REF(dwork1, irow) * dluval[iel];
    }
    dwork1[i-1] = dv2;
  }
  if (i>jpiv) {
    int i1 = mcstrt[i];
    double dv1 = dwork1[i];
    for (; iel < i1; iel++) {
      int irow = hrowi[iel];
      dv1 += SHIFT_REF(dwork1, irow) * dluval[iel];
    }
    dwork1[i] = dv1;
  }
}
