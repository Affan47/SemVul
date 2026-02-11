kordstat(x,k,n,ind)
double *x;
INT k, n, *ind;
{ INT i, i0, i1, l, r;
  double piv;
  if (k<1) return(0.0);
  i0 = 0; i1 = n-1;
  while (1)
  { piv = x[ind[(i0+i1)/2]];
    l = i0; r = i1;
    while (l<=r)
    { while ((l<=i1) && (x[ind[l]]<=piv)) l++;
      while ((r>=i0) && (x[ind[r]]>piv)) r--;
      if (l<=r) ISWAP(ind[l],ind[r]);
    }
    if (r<k-1) i0 = l;
    else
    { for (i=i0; i<=r; )
        if (x[ind[i]]==piv) { ISWAP(ind[i],ind[r]); r--; }
        else i++;
      if (r<k-1) return(piv);
      i1 = r;
    }
  }
}
