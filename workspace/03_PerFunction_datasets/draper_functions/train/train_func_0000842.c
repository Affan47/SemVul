matrix_assign_variable(pk_internal_t* pk,
				 bool destructive,
				 matrix_t* mat,
				 ap_dim_t dim, numint_t* tab)
{
  size_t i,j,var;
  bool den;
  matrix_t* nmat;

  var = pk->dec + dim;
  den = numint_cmp_int(tab[0],1)>0;

  nmat =
    destructive ?
    mat :
    _matrix_alloc_int(mat->nbrows,mat->nbcolumns,false);

  nmat->_sorted = false;

  for (i=0; i<mat->nbrows; i++){

    vector_product(pk,pk->matrix_prod,
		   mat->p[i],
		   tab,mat->nbcolumns);

    if (!destructive){

      numint_init_set(nmat->p[i][0],mat->p[i][0]);
      for (j=1; j<mat->nbcolumns; j++){
	if (j!=var){
	  numint_init_set(nmat->p[i][j],mat->p[i][j]);
	  if (den){
	    numint_mul(nmat->p[i][j],mat->p[i][j],tab[0]);
	  }
	}
      }
    }
    else {

      for (j=0; j<mat->nbcolumns; j++){
	if (j!=var){
	  if (den)
	    numint_mul(nmat->p[i][j],mat->p[i][j],tab[0]);
	  else
	    numint_set(nmat->p[i][j],mat->p[i][j]);
	}
      }
    }

    if (!destructive)
      numint_init_set(nmat->p[i][var],pk->matrix_prod);
    else
      numint_set(nmat->p[i][var],pk->matrix_prod);

    matrix_normalize_row(pk,nmat,i);
  }
  return nmat;
}
