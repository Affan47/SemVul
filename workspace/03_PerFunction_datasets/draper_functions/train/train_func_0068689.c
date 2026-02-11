GGadgetIsEnabled(GGadget *g) {
    if ( g->state==gs_invisible )
return( !g->was_disabled );
return( g->state==gs_enabled );
}
