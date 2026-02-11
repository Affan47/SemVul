consys_mulaccumcol (consys_struct *consys, int colndx,
			 double scalar, double *vec)


{ colhdr_struct *colhdr ;
  coeff_struct *coeff ;

# if defined(DYLP_PARANOIA) || !defined(DYLP_NDEBUG)
  const char *rtnnme = "consys_accumcol" ;
# endif

# ifdef DYLP_PARANOIA
  if (consys == NULL)
  { errmsg(2,rtnnme,"consys") ;
    return (FALSE) ; }
  if (consys->mtx.cols == NULL)
  { errmsg(101,rtnnme,consys->nme,"column header") ;
    return (FALSE) ; }
# endif
# ifndef DYLP_NDEBUG
  if (colndx <= 0 || colndx > consys->varcnt)
  { errmsg(102,rtnnme,consys->nme,"column",colndx,1,consys->varcnt) ;
    return (FALSE) ; }
# endif
  colhdr = consys->mtx.cols[colndx] ;
# ifdef DYLP_PARANOIA
  if (colhdr == NULL)
  { errmsg(103,rtnnme,consys->nme,"column",colndx) ;
    return (FALSE) ; }
  if (colndx != colhdr->ndx)
  { errmsg(126,rtnnme,consys->nme,"column",colhdr,colhdr->ndx,colndx,colhdr) ;
    return (FALSE) ; }
  if (vec == NULL)
  { errmsg(2,rtnnme,"vec") ;
    return (FALSE) ; }
# endif

  for (coeff = colhdr->coeffs ; coeff != NULL ; coeff = coeff->colnxt)
  {
#   ifdef DYLP_PARANOIA
    if (coeff->rowhdr == NULL)
    { errmsg(125,rtnnme,consys->nme,"rowhdr",coeff,"column",
	     consys_nme(consys,'v',colndx,FALSE,NULL),colndx) ;
      return (FALSE) ; }
    if (coeff->rowhdr->ndx <= 0 || coeff->rowhdr->ndx > consys->concnt)
    { errmsg(102,rtnnme,consys->nme,"row",coeff->rowhdr->ndx,
	     1,consys->concnt) ;
      return (FALSE) ; }
    if (coeff->rowhdr != consys->mtx.rows[coeff->rowhdr->ndx])
    { errmsg(126,rtnnme,consys->nme,"row",coeff->rowhdr,coeff->rowhdr->ndx,
	     coeff->rowhdr->ndx,consys->mtx.rows[coeff->rowhdr->ndx]) ;
      return (FALSE) ; }
#   endif
    vec[coeff->rowhdr->ndx] += scalar*coeff->val ; }

  return (TRUE) ; }
