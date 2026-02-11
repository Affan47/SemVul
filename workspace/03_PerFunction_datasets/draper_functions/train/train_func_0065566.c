matrix( FMField *mtx, FMField *xi, FMField *e_coors, FMField *bfg )
{
  int32 nEP = bfg->nCol, dim = bfg->nRow, iep;

  if (dim == 3) {
    for (iep = 0; iep < nEP; iep++) {
      bfg->val[0*nEP+iep] = baseTriLx( xi->val[0], xi->val[1], xi->val[2], iep );
      bfg->val[1*nEP+iep] = baseTriLy( xi->val[0], xi->val[1], xi->val[2], iep );
      bfg->val[2*nEP+iep] = baseTriLz( xi->val[0], xi->val[1], xi->val[2], iep );
    }
  } else {
    for (iep = 0; iep < nEP; iep++) {
      bfg->val[0*nEP+iep] = baseBiLx( xi->val[0], xi->val[1], iep );
      bfg->val[1*nEP+iep] = baseBiLy( xi->val[0], xi->val[1], iep );
    }
  }

  fmf_mulAB_n1( mtx, bfg, e_coors );
}
