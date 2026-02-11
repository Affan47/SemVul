deactNBPrimArchList (consys_struct *orig_sys,
				   int cnt, int *avndxs)


{ int k ;
  bool retval ;
  const char *rtnnme = "deactNBPrimArchList" ;

# ifdef DYLP_PARANOIA
  if (avndxs == NULL)
  { errmsg(2,rtnnme,"avndxs") ;
    return (FALSE) ; }
  if (cnt <= 0 || cnt > dy_sys->archvcnt)
  { errmsg(5,rtnnme,"cnt",cnt) ;
    return (FALSE) ; }
# endif


  qsort(&avndxs[0],cnt,sizeof(int),intcompare) ;

  retval = TRUE ;
  for (k = 0 ; k < cnt && retval == TRUE ; k++)
  {
#   ifndef DYLP_NDEBUG
    if (dy_opts->print.varmgmt >= 2)
    { dyio_outfmt(dy_logchn,dy_gtxecho,"\n    deactivating variable %s (%d)",
		  consys_nme(dy_sys,'v',avndxs[k],TRUE,NULL),avndxs[k]) ; }
#   endif
    retval = dy_deactNBPrimArch(orig_sys,avndxs[k]) ;
    if (retval == FALSE)
    { errmsg(430,rtnnme,
	     dy_sys->nme,dy_prtlpphase(dy_lp->phase,TRUE),dy_lp->tot.iters,
	     "deactivate","variable",
	     consys_nme(dy_sys,'v',avndxs[k],TRUE,NULL),avndxs[k]) ; } }

# ifdef DYLP_PARANOIA
  if (retval == TRUE)
  { retval = dy_chkdysys(orig_sys) ; }
# endif

  return (retval) ; }
