getComponentColour(colour c, int component) {
	if( component == 0 ) {
		return makeColour( c.r, 0, 0 );
	}
	else if( component == 1 ) {
		return makeColour( 0, c.g, 0 );
	}
	else if( component == 2 ) {
		return makeColour( 0, 0, c.b );
	}
	return COLOUR_BLACK;
}
