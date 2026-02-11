scanPrimVarDualInfeas (fdcand_struct **p_fdcands)


{ int j,n,purgecnt,flipcnt ;
  fdcand_struct *fdcands ;
  double cbarj,lbj,ubj ;
  double *vlb,*vub ;
  flags statj ;
  bool purge ;

# ifdef DYLP_PARANOIA

  const char *rtnnme = "scanPrimVarDualInfeas" ;

  if (p_fdcands == NULL)
  { errmsg(2,rtnnme,"fdcands") ;
    return (-1) ; }
# endif


  n = dy_sys->varcnt ;
  vlb = dy_sys->vlb ;
  vub = dy_sys->vub ;
  purgecnt = 0 ;
  if (*p_fdcands == NULL)
  { fdcands =
      (fdcand_struct *) MALLOC((dy_sys->archvcnt+1)*sizeof(fdcand_struct)) ; }
  else
  { fdcands = *p_fdcands ; }


  flipcnt = 0 ;
  for (j = 1 ; j <= n ; j++)
  { purge = FALSE ;
    statj = dy_status[j] ;
    cbarj = dy_cbar[j] ;
    if ((flgon(statj,vstatNBLB) && cbarj < -dy_tols->dfeas) ||
        (flgon(statj,vstatNBUB) && cbarj > dy_tols->dfeas))
    { fdcands[++purgecnt].ndx = j ;
      fdcands[purgecnt].flippable = FALSE ;
      lbj = vlb[j] ;
      ubj = vub[j] ;
      if (flgon(statj,vstatNBLB))
      { if (ubj < dy_tols->inf)
	{ fdcands[purgecnt].flippable = TRUE ;
	  flipcnt++ ;
	  fdcands[purgecnt].delta = ubj-lbj ; } }
      else
      { if (lbj > -dy_tols->inf)
	{ fdcands[purgecnt].flippable = TRUE ;
	  flipcnt++ ;
	  fdcands[purgecnt].delta = lbj-ubj ; } }
#     ifndef DYLP_NDEBUG
      if (dy_opts->print.force >= 3)
      { dyio_outfmt(dy_logchn,dy_gtxecho,
		    "\n      queuing %s (%d) for %s, %s, cbar<%d> = %g",
		    consys_nme(dy_sys,'v',j,TRUE,NULL),j,
		    (fdcands[purgecnt].flippable == TRUE)?"flip":"deactivation",
		    dy_prtvstat(statj),j,cbarj) ; }
#     endif
    } }


  if (purgecnt == 0)
  { if (*p_fdcands == NULL)
    { FREE(fdcands) ; } }
  else
  { if (flipcnt > 0)
      fdcands[0].flippable = TRUE ;
    else
      fdcands[0].flippable = FALSE ;
    if (*p_fdcands == NULL)
      *p_fdcands = fdcands ; }

# ifndef DYLP_NDEBUG
  if (dy_opts->print.force >= 2)
  { dyio_outfmt(dy_logchn,dy_gtxecho,
	        "\n    queued %d variables, %d deactivate, %d flip.",
	        purgecnt,purgecnt-flipcnt,flipcnt) ; }
# endif

  return (purgecnt) ; }
