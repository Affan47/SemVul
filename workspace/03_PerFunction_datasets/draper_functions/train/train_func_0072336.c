PuntEvent( node, ev )
  nptr   node;
  evptr  ev;
  {
    if( node->nflags & WATCHED )
	lprintf( stdout,
	  "    punting transition of %s -> %c scheduled for %2.2fns\n",
	  node->nname, vchars[ev->eval], d2ns( ev->ntime ) );

    ASSERT( node == ev->enode )
      {
	lprintf( stderr, "bad punt @ %d for %s\n", cur_delta, node->nname );
	node->events = NULL;
	return;
      }

    if( ev->type != DECAY_EV )
	AddPunted( ev->enode, ev, cur_delta );
    free_event( ev );
  }
