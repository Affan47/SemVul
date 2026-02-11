luf_adjustsize (void)


{ double upd_tol,piv_tol,zero_tol,max_gro ;
  int factor,look,capacity ;
# ifndef DYLP_NDEBUG
  int oldcapacity ;
# endif


  if (dy_sys->concnt > luf_capacity)
  { factor = luf_basis->hh_max ;
    upd_tol = luf_basis->upd_tol ;
    zero_tol = luf_basis->luf->eps_tol ;
    piv_tol = luf_basis->luf->piv_tol ;
    look = luf_basis->luf->piv_lim ;
    max_gro = luf_basis->luf->max_gro ;
#   ifndef DYLP_NDEBUG
    oldcapacity = luf_basis->m ;
#   endif
    dy_freebasis() ;
    capacity = (int) (dy_sys->concnt*1.5) ;
    dy_initbasis(capacity,factor,zero_tol) ;
    luf_basis->upd_tol = upd_tol ;
    luf_basis->luf->eps_tol = zero_tol ;
    luf_basis->luf->piv_tol = piv_tol ;
    luf_basis->luf->piv_lim = look ;
    luf_basis->luf->max_gro = max_gro ;
#   ifndef DYLP_NDEBUG
    if (dy_opts->print.basis >= 2)
    { dyio_outfmt(dy_logchn,dy_gtxecho,
		  "\n    increased basis capacity from %d to %d constraints",
		  oldcapacity,luf_basis->m) ;
      dyio_outfmt(dy_logchn,dy_gtxecho,", piv lim %d.",luf_basis->hh_max) ; }
#   endif
  }


  luf_basis->m = dy_sys->concnt ;
  luf_basis->luf->n = dy_sys->concnt ;

  return ; }
