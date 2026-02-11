GetStemCounterZone( StemData *stem, DBounds *orig_b ) {
    uint8 ret = 0, by_x;
    int i;
    double min, max, middle, fudge, s, e;

    if ( stem == NULL )
return( czone_top | czone_bot );
    by_x = ( stem->unit.x > stem->unit.y );
    min = by_x ? orig_b->minx : orig_b->miny;
    max = by_x ? orig_b->maxx : orig_b->maxy;
    middle = ( max - min )/2.;
    fudge = ( max - min )/16.;

    for ( i=0; i<stem->activecnt && ret < 3; i++ ) {
	s = (&stem->left.x)[!by_x] +
	    stem->active[i].start * (&stem->unit.x)[!by_x];
	e = (&stem->left.x)[!by_x] +
	    stem->active[i].end * (&stem->unit.x)[!by_x];
	if ( s < middle - fudge || e < middle - fudge )
	    ret |= czone_bot;
	if ( e > middle + fudge || s > middle + fudge )
	    ret |= czone_top;
    }
return( ret );
}
