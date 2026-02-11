dy_calcobj (void)


{ int vndx ;
  double z ;

#ifdef DYLP_PARANOIA
  const char *rtnnme = "dy_calcobj" ;

  if (dy_x == NULL)
  { errmsg(2,rtnnme,"dy_x") ;
    return (quiet_nan(0)) ; }
  if (dy_sys == NULL)
  { errmsg(2,rtnnme,"dy_sys") ;
    return (quiet_nan(0)) ; }
  if (dy_sys->obj == NULL)
  { errmsg(2,rtnnme,"dy_sys->obj") ;
    return (quiet_nan(0)) ; }
#endif

  z = 0.0 ;
  for (vndx = 1 ; vndx <= dy_sys->varcnt ; vndx++)
    if (dy_x[vndx] != 0.0) z += dy_sys->obj[vndx]*dy_x[vndx] ;
  if (dy_lp->p1obj.installed == FALSE) z += dy_lp->inactzcorr ;
  setcleanzero(z,dy_tols->zero) ;

  return (z) ; }
