convertBitOrder( Endian bitOrder ) const
{
    if ( isNull() || data->d != 1 ||
	 !(bitOrder == BigEndian || bitOrder == LittleEndian) ) {
	QImage nullImage;
	return nullImage;
    }
    if ( data->bitordr == bitOrder )
	return copy();

    QImage image( data->w, data->h, 1, data->ncols, bitOrder );

    int bpl = (width() + 7) / 8;
    for ( int y = 0; y < data->h; y++ ) {
	register uchar *p = jumpTable()[y];
	uchar *end = p + bpl;
	uchar *b = image.jumpTable()[y];
	while ( p < end )
	    *b++ = bitflip[*p++];
    }
    memcpy( image.colorTable(), colorTable(), numColors()*sizeof(QRgb) );
    return image;
}
