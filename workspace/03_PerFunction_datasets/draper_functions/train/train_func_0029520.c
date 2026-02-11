operator==( const QImage & i ) const
{

    if ( i.data == data )
	return true;

    if ( i.data->h != data->h ||
	 i.data->w != data->w )
	return false;

    QImage i1 = convertDepth( 32 );
    QImage i2 = i.convertDepth( 32 );
    int l;
    for( l=0; l < data->h; l++ )
	if ( memcmp( i1.scanLine( l ), i2.scanLine( l ), 4*data->w ) )
	    return false;
    return true;
}
