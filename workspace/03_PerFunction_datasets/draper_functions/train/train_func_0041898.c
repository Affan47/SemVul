ghosted( unsigned char *dest, unsigned char *src,
	unsigned char transparency )
{
	double alphamax = ((double) 255*((double) 255/(double) transparency));

	for( int y = height; y--; dest += padding )
		for( int x = width; x--; )
			if( !(*((int *) src) & 0xff000000) )
			{
				src += 4;
				dest += 3;
			}
			else
			{
				double diff;
				double mod = alphamax/(double) (*(src+3));


				register int red = *(src++);
				register int green = *(src++);
				register int blue = *(src++);
				register int grey = (red+green+blue)/3;

				diff = grey;
				diff -= *dest;
				diff /= mod;
				*(dest++) += (int) diff;

				diff = grey;
				diff -= *dest;
				diff /= mod;
				*(dest++) += (int) diff;

				diff = grey;
				diff -= *dest;
				diff /= mod;
				*(dest++) += (int) diff;

				src++;
			}
}
