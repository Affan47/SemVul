sobolev_area_hess(f_info)
struct qinfo *f_info;
{
  MAT2D(Ainv,MAXCOORD,MAXCOORD);
  MAT2D(FtAinv,MAXCOORD,MAXCOORD);
  MAT2D(FtAF,MAXCOORD,MAXCOORD);
  int i,j,m,n;
  int dim = web.dimension;
  REAL area;

  mat_mul_tr(f_info->sides[0],f_info->sides[0],Ainv,dim,SDIM,dim);
  area = det_adjoint(Ainv,dim);
  if ( area == 0.0 ) return area;
  for ( i = 0 ; i < dim ; i++ )
     for ( j = 0 ; j < dim  ; j++ )
        Ainv[i][j] /= area;
  area = sqrt(area)/web.simplex_factorial;

  tr_mat_mul(f_info->sides[0],Ainv,FtAinv,dim,SDIM,dim);
  mat_mult(FtAinv,f_info->sides[0],FtAF,SDIM,dim,SDIM);


  for ( i = 0 ; i < dim ; i++ )
     for ( j = 0 ; j < SDIM ; j++ )
     { f_info->grad[i+1][j] = FtAinv[j][i]*area;
        f_info->grad[0][j] -= FtAinv[j][i]*area;
     }


  for ( m = 0 ; m < dim ; m++ )
     for ( n = 0 ; n < dim ; n++ )
        for ( i = 0 ; i < SDIM ; i++ )
          for ( j = 0 ; j < SDIM ; j++ )
          { REAL val;
             val = (i==j) ? Ainv[m][n] : 0.0;
             val -= FtAF[i][j]*Ainv[m][n];
             val += FtAinv[i][m]*FtAinv[j][n];
             val *= area;
             f_info->hess[m+1][n+1][i][j] += val;
             f_info->hess[0][n+1][i][j] -= val;
             f_info->hess[m+1][0][i][j] -= val;
             f_info->hess[0][0][i][j] += val;
          }
  return area;
}
