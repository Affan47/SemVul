sp_solution(S,rhs,X)
struct linsys *S;
REAL *rhs;
REAL *X;
{
  REAL *Y;
  REAL *Z;
  REAL *W;
  int i;

  if ( S->low_rank == 0 )
  {
    (*sp_solve_func)(S,rhs,X);
    return;
  }


  Y = (REAL*)temp_calloc(S->N,sizeof(REAL));
  Z = (REAL*)temp_calloc(S->low_rank, sizeof(REAL));
  W = (REAL*)temp_calloc(S->low_rank, sizeof(REAL));
  (*sp_solve_func)(S,rhs,Y);
  matvec_mul(S->low_rank_vectors,Y,Z,S->low_rank,S->low_rank_vecsize);
  matvec_mul(S->low_rank_form,Z,W,S->low_rank,S->low_rank);
  matvec_mul(S->low_rank_inverse_form,W,Z,S->low_rank,S->low_rank);
  vec_mat_mul(Z,S->low_rank_vectors,Y,S->low_rank,S->low_rank_vecsize);
  for ( i = 0 ;  i < S->low_rank_vecsize ; i++ )
    Y[i] = rhs[i] - Y[i];
  for ( ; i < S->N ; i++ )
    Y[i] = rhs[i];
  (*sp_solve_func)(S,Y,X);

  temp_free((char*)Y);
  temp_free((char*)Z);
  temp_free((char*)W);
}
