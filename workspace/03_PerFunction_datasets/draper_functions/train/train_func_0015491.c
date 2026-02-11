GListBGetFirst(GGadget *g) {
    int i;
    GListButton *gl = (GListButton *) g;

    for ( i=0; i<gl->ltot; ++i )
	if ( gl->ti[i]->selected )
return( i );

return( -1 );
}
