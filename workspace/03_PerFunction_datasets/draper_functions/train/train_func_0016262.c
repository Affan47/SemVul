c_ekkbtj4p_no_dense(const int nrow,const double * COIN_RESTRICT dluval,
				const int * COIN_RESTRICT hrowi,
				const int * COIN_RESTRICT mcstrt,
				double * COIN_RESTRICT dwork1, int ndo,int jpiv)
{
  int i;
  double dv1;
  int iel;
  int irow;
  int i1,i2;


  for (i=nrow;i >=1;i--) {
    if (dwork1[i]) {
      break;
    }
  }
  i--;
  if (i>ndo+jpiv) {
    i=ndo+jpiv;
  }
  mcstrt -= jpiv;
  i2=mcstrt[i+1];
  for (; i > jpiv; --i) {
    double dv1b=0.0;
    int nel;
    i1 = mcstrt[i];
    nel= i1-i2;
    dv1 = dwork1[i];
    iel=i2;
    if ((nel&1)!=0) {
      irow = hrowi[iel];
      dv1b = SHIFT_REF(dwork1, irow) * dluval[iel];
      iel++;
    }
    for ( ; iel < i1; iel+=2) {
      int irow = hrowi[iel];
      int irowb = hrowi[iel+1];
      dv1 += SHIFT_REF(dwork1, irow) * dluval[iel];
      dv1b += SHIFT_REF(dwork1, irowb) * dluval[iel+1];
    }
    i2=i1;
    dwork1[i] = dv1+dv1b;
  }
}
