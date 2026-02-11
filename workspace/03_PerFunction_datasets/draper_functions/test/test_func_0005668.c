DGG_generateFormulationCuts( DGG_list_t *cut_list,
				 DGG_data_t *data,
				 const void *solver_ptr,
				 int nrows,
				 CoinThreadRandom & generator)
{
  int k, rval = 0;
  DGG_constraint_t *base = NULL;
  int num_rows = (data->nrow < nrows) ? data->nrow : nrows;
  int nc = cut_list->n;

  base = DGG_newConstraint(data->ncol + data->nrow);

  if(talk) printf ("2mir_test: generating form row cuts %d\n", num_rows);
  for(k=0; k<num_rows; k++) {
    base->nz = 0;

    rval = DGG_getFormulaConstraint(k, solver_ptr, data, base);
    DGG_CHECKRVAL1(rval, rval);


    rval = DGG_generateFormulationCutsFromBase(base, data->x[data->ncol+k],
					       cut_list, data, solver_ptr,
					       generator);
    DGG_CHECKRVAL1(rval, rval);
    if (base->nz == 0){
#ifdef COIN_DEVELOP
      printf ("why does constraint not exist ?\n");
#endif
      continue;
    }
  }

 CLEANUP:
  if(talk) printf ("2mir_test: generated %d form cuts\n", cut_list->n - nc); fflush (stdout);
  DGG_freeConstraint(base);
  return rval;
}
