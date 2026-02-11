pk_internal_clear(pk_internal_t* pk)
{
  size_t i;

  if (pk->vector_numintp) vector_free(pk->vector_numintp,pk->maxcols);
  pk->vector_numintp = 0;

  if (pk->vector_tmp) vector_free(pk->vector_tmp,5);
  pk->vector_tmp = 0;

  if (pk->vector_mpqp){
    for (i=0; i<pk->maxdims+3; i++)
      mpq_clear(pk->vector_mpqp[i]);
    free(pk->vector_mpqp);
  }
  pk->vector_mpqp = 0;

  if (pk->matrix_dimp) free(pk->matrix_dimp);
  pk->matrix_dimp = 0;

  numint_clear(pk->matrix_acc);
  numint_clear(pk->matrix_prod);


  if (pk->cherni_intp) free(pk->cherni_intp);
  pk->cherni_intp = 0;

  numint_clear(pk->cherni_prod);

  if (pk->itv) itv_internal_free(pk->itv);
  pk->itv = 0;
  bound_clear(pk->poly_bound);
  itv_clear(pk->poly_itv);
  itv_linexpr_clear(&pk->poly_itv_linexpr);
  itv_lincons_clear(&pk->poly_itv_lincons);
  numrat_clear(pk->poly_numrat);
  if (pk->poly_numintp) vector_free(pk->poly_numintp, pk->maxcols);
  pk->poly_numintp = 0;

  if (pk->poly_numintp2) vector_free(pk->poly_numintp2, pk->maxcols);
  pk->poly_numintp2 = 0;

  if (pk->poly_dimp) free(pk->poly_dimp);
  pk->poly_dimp = 0;
  if (pk->poly_dimp2) free(pk->poly_dimp2);
  pk->poly_dimp2 = 0;
  if (pk->poly_fold_dimp) free(pk->poly_fold_dimp);
  pk->poly_fold_dimp = 0;


  if (pk->poly_matspecial) matrix_free(pk->poly_matspecial);
  pk->poly_matspecial = 0;

  numint_clear(pk->poly_prod);

  pk->maxdims = 0;
  pk->maxrows = 0;
  pk->maxcols = 0;
}
