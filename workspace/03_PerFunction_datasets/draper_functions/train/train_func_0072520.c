activeMark( unsigned char *dest, MarkType type,
	int left, int top )
{
	Render::Mark mark = getMark( type );

	dest += getOffset( left, top, mark, 3 );

	int skip = bytesperline-(mark.getWidth()*3);
	const char *src = mark.getPixels();

	for( int y = mark.getHeight(); y--; dest += skip )
		for( int x = mark.getWidth(); x--; )
			if( *(src++) )
			{
				*(dest++) ^= 0xff;
				*(dest++) ^= 0xff;
				*(dest++) ^= 0xff;
			}
}
