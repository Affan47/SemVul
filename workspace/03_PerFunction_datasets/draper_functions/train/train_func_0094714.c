simplex_quadrature(dim,order,maxpt,x,w)
int dim;
int order;
int maxpt;
REAL **x;
REAL *w;
{ int N = 1+order/2;
  int bsize;
  int iter[100];
  int n;
  int count;
  int depth;
  REAL **gj_x;
  REAL **gj_w;
  REAL coeff;

  if ( N < 2 ) N = 2;

  for ( n = 0, bsize = 1 ; n < dim ; n++ ) bsize *= N;
  if ( bsize > maxpt ) { puts("too few points.\n"); exit(1); }

  gj_x = dmatrix(0,dim-1,0,N);
  gj_w = dmatrix(0,dim-1,0,N);


  for ( n = 0 ; n < dim ; n++ )
     gauss_jacobi(N,(REAL)n,gj_x[n],gj_w[n]);


  coeff = (REAL)(1 << ((dim*(dim+1))/2));
  for ( n = 1 ; n <= dim ; n++ ) coeff /= n;


  for ( n = 0 ; n < dim ; n++ ) iter[n] = 0;

  count = 0;
  do
  { REAL prod;


     for ( w[count] = 1., n = 0 ; n < dim ; n++ )
        w[count] *= gj_w[dim-1-n][iter[n]];
     w[count] /= coeff;

     for ( prod = 1., n = 0, x[count][dim] = 1.0 ; n < dim ; n++ )
     { x[count][n] = (1-gj_x[dim-1-n][iter[n]])/2*prod;
        x[count][dim] -= x[count][n];
        prod *= 1 - (1-gj_x[dim-1-n][iter[n]])/2;
     }
     count++;

     depth = dim-1;
     while ( ++iter[depth] >= N )
     { iter[depth] = 0;
        depth--;
        if ( depth < 0 ) break;
     }
  } while ( depth >= 0 );

  free_matrix(gj_x);
  free_matrix(gj_w);
  return count;
}
