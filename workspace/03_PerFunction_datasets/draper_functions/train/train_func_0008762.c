QR_full(A,evalues,n,M)
REAL **A;
REAL *evalues;
int n;
struct linsys *M;
{ REAL **Q,**L;
  int i,j;
  REAL resid;
  int count = 0;

  Q = dmatrix(0,n-1,0,n-1);
  L = dmatrix(0,n-1,0,n-1);
  do
  { LQ_decomp(A,n,n,Q,L,M);
     mat_mult(Q,L,A,n,n,n);
     for ( i = 0, resid = 0.0 ; i < n ; i++ )
      for ( j = 0 ; j < i ; j++ )
         resid += fabs(A[i][j]);
#ifdef LONGDOUBLE
     sprintf(msg,"QR residual %*.*Lf\n",DWIDTH,DPREC,resid);
#else
     sprintf(msg,"QR residual %20.15f\n",resid);
#endif
     outstring (msg);
  } while ( (resid > 1000*machine_eps) && (count++ < 20) );
  for ( i = 0 ; i < n ; i++ ) evalues[i] = A[i][i];
}
