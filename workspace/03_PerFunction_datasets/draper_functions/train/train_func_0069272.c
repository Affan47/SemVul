EvalStimulus()
  {
    evptr  ev;
    int    n_active;
    nptr   nd;

    for( ev = stim_evs; ev != NULL; ev = ev->nlink )
      {
	nd = ev->enode;
	n_active = EvalSrcDrn( nd, FALSE );

	if( not n_active )
	    nd->nflags &= ~STIM;
	else if( nd->nflags & STIM )
	  {
	    register hptr  h;

	    NEXTH( h, nd->curr );
	    if( not EnqueueHist( nd, h, STIMULI ) )
		nd->nflags &= ~STIM;
	  }
      }
  }
