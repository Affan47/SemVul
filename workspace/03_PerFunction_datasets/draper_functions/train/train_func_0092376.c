poly_set_top(pk_internal_t* pk, pk_t* po)
{
  size_t i;
  size_t dim;

  if (po->C) matrix_free(po->C);
  if (po->F) matrix_free(po->F);
  if (po->satC) satmat_free(po->satC);
  if (po->satF) satmat_free(po->satF);

  po->status =
    pk_status_conseps |
    pk_status_consgauss |
    pk_status_gengauss |
    pk_status_minimaleps
    ;

  dim = po->intdim + po->realdim;

  po->C = matrix_alloc(pk->dec-1, pk->dec+dim,true);
  po->F = matrix_alloc(pk->dec+dim-1,pk->dec+dim,true);

  po->satC = satmat_alloc(pk->dec+dim-1,bitindex_size(pk->dec-1));
  po->satF = 0;
  po->nbeq = 0;
  po->nbline = dim;


  matrix_fill_constraint_top(pk,po->C,0);


  for(i=0; i<dim; i++){
    numint_set_int(po->F->p[i][pk->dec+dim-1-i],1);
  }
  if (pk->strict){

    numint_set_int(po->F->p[dim][0],1);
    numint_set_int(po->F->p[dim][polka_cst],1);
    numint_set_int(po->F->p[dim+1][0],1);
    numint_set_int(po->F->p[dim+1][polka_cst],1);
    numint_set_int(po->F->p[dim+1][polka_eps],1);

    po->satC->p[dim][0] = bitstring_msb >> 1;
    po->satC->p[dim+1][0] = bitstring_msb;
  }
  else {

    numint_set_int(po->F->p[dim][0],1);
    numint_set_int(po->F->p[dim][polka_cst],1);

    po->satC->p[dim][0] = bitstring_msb;
  }
  assert(poly_check(pk,po));
}
