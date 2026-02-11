convert_1_to_8( const QImage *src, QImage *dst )
{
    if ( !dst->create(src->width(), src->height(), 8, 2) )
	return false;
    dst->setAlphaBuffer( src->hasAlphaBuffer() );
    if (src->numColors() >= 2) {
	dst->setColor( 0, src->color(0) );
	dst->setColor( 1, src->color(1) );
    } else {

	if (src->numColors() >= 1)
	    dst->setColor( 0, src->color(0) );
	else
	    dst->setColor( 0, 0xffffffff );
	dst->setColor( 1, 0xff000000 );
    }
    for ( int y=0; y<dst->height(); y++ ) {
	register uchar *p = dst->scanLine(y);
	uchar *b = src->scanLine(y);
	int x;
	if ( src->bitOrder() == QImage::BigEndian ) {
	    for ( x=0; x<dst->width(); x++ ) {
		*p++ = (*b >> (7 - (x & 7))) & 1;
		if ( (x & 7) == 7 )
		    b++;
	    }
	} else {
	    for ( x=0; x<dst->width(); x++ ) {
		*p++ = (*b >> (x & 7)) & 1;
		if ( (x & 7) == 7 )
		    b++;
	    }
	}
    }
    return true;
}
