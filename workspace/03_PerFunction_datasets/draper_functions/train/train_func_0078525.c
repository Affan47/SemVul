factor_loadcol (void *p_consys, int i, int *rndx, double *coeff)


{ int j,vecndx,pkndx ;
  double aij ;
  pkvec_struct *aj ;
  consys_struct *consys ;

  const char *rtnnme = "factor_loadcol" ;

# ifdef DYLP_PARANOIA
  if (p_consys == NULL)
  { errmsg(2,rtnnme,"consys") ;
    return (-1) ; }
  if (rndx == NULL)
  { errmsg(2,rtnnme,"row index vector") ;
    return (-1) ; }
  if (coeff == NULL)
  { errmsg(2,rtnnme,"coefficient") ;
    return (-1) ; }
# endif

  consys = (consys_struct *) p_consys ;
  aj = pkvec_new(consys->maxcollen) ;


  j = dy_basis[i] ;
  if (consys_getcol_pk(consys,j,&aj) == FALSE)
  { errmsg(112,rtnnme,dy_sys->nme,"retrieve","column",
	   consys_nme(dy_sys,'v',j,FALSE,NULL),j) ;
    if (aj != NULL) pkvec_free(aj) ;
    return (-1) ; }


  vecndx = 1 ;
  for (pkndx = 0 ; pkndx < aj->cnt ; pkndx++)
  { aij = aj->coeffs[pkndx].val ;
    if (aij != 0.0)
    { rndx[vecndx] = aj->coeffs[pkndx].ndx ;
      coeff[vecndx] = aij ;
      vecndx++ ; } }


  pkvec_free(aj) ;
  return (vecndx-1) ; }
