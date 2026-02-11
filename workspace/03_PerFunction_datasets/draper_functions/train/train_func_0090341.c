commonstart (start_enum start)


{ const char *rtnnme = "commonstart" ;


  if (start != startHOT)
  { if (consys_attach(dy_sys,CONSYS_COL,
		      sizeof(int),(void **) &dy_brkout) == FALSE)
    { errmsg(100,rtnnme,dy_sys->nme,"breakout vector") ;
      return (FALSE) ; }
    if (consys_attach(dy_sys,CONSYS_COL,
		      sizeof(int),(void **) &dy_degenset) == FALSE)
    { errmsg(100,rtnnme,dy_sys->nme,"primal degenerate set vector") ;
      return (FALSE) ; }
    if (consys_attach(dy_sys,CONSYS_ROW,
		      sizeof(int),(void **) &dy_ddegenset) == FALSE)
    { errmsg(100,rtnnme,dy_sys->nme,"dual degenerate set vector") ;
      return (FALSE) ; }
      }
  dy_lp->degen = 0 ;


  if (start != startHOT)
  { dy_initpivrej(dy_sys->varcnt/10) ; }


  if (start != startHOT)
  { if (consys_attach(dy_sys,CONSYS_ROW,
		      sizeof(double),(void **) &dy_gamma) == FALSE)
    { errmsg(100,rtnnme,dy_sys->nme,"column norm vector") ;
      return (FALSE) ; }
    if (consys_attach(dy_sys,CONSYS_ROW,
		      sizeof(bool),(void **) &dy_frame) == FALSE)
    { errmsg(100,rtnnme,dy_sys->nme,"reference frame vector") ;
      return (FALSE) ; }
    if (consys_attach(dy_sys,CONSYS_COL,
		      sizeof(double),(void **) &dy_rho) == FALSE)
    { errmsg(100,rtnnme,dy_sys->nme,"basis inverse row norm") ;
      return (FALSE) ; } }


  if (dy_lp->simplex.next == dyDUAL)
  { dy_dseinit() ;
    dy_lp->simplex.init_dse = FALSE ;
    dy_lp->simplex.init_pse = TRUE ; }
  else
  { dy_pseinit() ;
    dy_lp->simplex.init_pse = FALSE ;
    dy_lp->simplex.init_dse = TRUE ; }

  return (TRUE) ; }
