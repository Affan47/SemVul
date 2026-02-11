grid_statement(sides side, int ticks_off, linedesc *ld,
		    shiftlist *sl, ticklist *tl) {
    tick *t;
    grid *g;
    linedesc defgrid(dotted, 0, 0);
    shiftcpy sc(&the_graph->base->griddef[side].shift);
    shiftdesc *sd;


    the_graph->base->tickdef[side].size = 0;


    if ( !ld ) ld = new linedesc;


    if ( ld->ld == def ) ld->ld = dotted;
    the_graph->base->griddef[side].desc = *ld;


    for_each(sl->begin(), sl->end(), sc);

    if ( ticks_off ) {
	if ( the_graph->base->griddef[side].prt )
	    delete the_graph->base->griddef[side].prt;
	the_graph->base->griddef[side].prt = 0;
    }
    if ( tl ) {
	the_graph->base->griddef[side].desc.ld = def;
	while (!tl->empty() ) {
	    t = tl->front();
	    tl->pop_front();

	    g = new grid(t);
	    g->side = side;
	    shiftcpy scy(&g->shift);

	    if ( ld ) {

		if ( ld->ld == def ) ld->ld = dotted;
  		g->desc = *ld;
	    }

	    for_each(sl->begin(), sl->end(), scy);

	    if ( ticks_off ) {
		if ( g->prt ) delete g->prt;
		g->prt = 0;
	    }
	    the_graph->base->gds.push_back(g);
	    if ( g->side == top_side || g->side == bottom_side )
		g->c->newx(g->where);
	    else
		g->c->newy(g->where);
	    delete t;
	}
	delete tl;
    }
    while ( !sl->empty() ) {
	sd = sl->front();
	sl->pop_front();
	delete sd;
    }
    delete sl;
    delete ld;
}
