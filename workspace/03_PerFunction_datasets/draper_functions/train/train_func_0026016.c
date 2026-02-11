add_tran_cap( t )
  register tptr  t;
  {
    if( t->gate->nflags & N_CAP_SET )
	t->gate->ncap += t->r->width * t->r->length * CTGA;

    if( config_flags & TDIFFCAP )
      {
	if( t->source->nflags & N_CAP_SET )
	    t->source->ncap += t->r->width * CTDW + CTDE;
	if( t->drain->nflags & N_CAP_SET )
	    t->drain->ncap += t->r->width * CTDW + CTDE;
      }
  }
