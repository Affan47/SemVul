dy_finalstats (lpstats_struct *lpstats)


{ int i,k ;

# ifdef DYLP_PARANOIA

  const char *rtnnme = "dy_finalstats" ;

  if (lpstats == NULL)
  { errmsg(2,rtnnme,"lpstats") ;
    return ; }
# endif


  for (k = 1 ; k <= dy_sys->concnt ; k++)
  { i = dy_actcons[k] ;
    if (i > 0)
    { lpstats->cons.fin[i] = TRUE ; } }


  lpstats->tot.iters = dy_lp->tot.iters ;
  lpstats->tot.pivs = dy_lp->tot.pivs ;

  return ; }
