b_qsort_matrix_columns_descending_real(PRECISION *x, int m, int n, int idx)
{
  PRECISION *y, c;
  int j, k, p, s;
  y=(PRECISION*)dw_malloc(s=m*sizeof(PRECISION));
  if (n > 10)
    {

      p=(n-1)*m;
      k=p+idx;

      if (x[idx] == x[k])
	c=x[idx];
      else
	{
	  if (x[idx] < x[k])
	    { memcpy(y,x+p,s); memcpy(x+p,x,s); memcpy(x,y,s); }
	  c=0.5*(x[idx] + x[k]);
	}

      for (j=m+idx; (j < p) && (x[j] >= c); j+=m);
      for (k-=m; (k > idx) && (x[k] <= c); k-=m);
      while (j < k)
	{
	  memcpy(y,x+j-idx,s); memcpy(x+j-idx,x+k-idx,s); memcpy(x+k-idx,y,s);
	  while (x[j] >= c) j+=m;
	  while (x[k] <= c) k-=m;
	}
      if (k > idx)
	b_qsort_matrix_columns_descending_real(x,m,(k-idx)/m+1,idx);
      if (j < p)
	b_qsort_matrix_columns_descending_real(x+j-idx,m,n-(j-idx)/m,idx);
    }
  else
    {

      p=n*m;
      for (j=m+idx; j < p; j+=m)
	if (x[j-m] < x[j])
	  {
	    memcpy(y,x+j-idx,s);
	    memcpy(x+j-idx,x+j-m-idx,s);
	    for (k=j-m-m; k >= 0; k-=m)
	      if (x[k] >= y[idx])
		break;
	      else
		memcpy(x+k+m-idx,x+k-idx,s);
	    memcpy(x+k+m-idx,y,s);
	  }
    }
  dw_free(y);
}
