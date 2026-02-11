IMGremapDecompress(char* desPtr, char* srcPtr, char* colorTable)
{
	int width = ((unsigned char*)srcPtr)[0] + (((unsigned char*)srcPtr)[1]<<8);
	int height = ((unsigned char*)srcPtr)[2] + (((unsigned char*)srcPtr)[3]<<8);

	((unsigned char*)desPtr)[0] = width;
	((unsigned char*)desPtr)[1] = width>>8;
	((unsigned char*)desPtr)[2] = height;
	((unsigned char*)desPtr)[3] = height>>8;
	int esi = 4;
	int destline = 4;
	int pixelsToSkip = 0;
	int al;

	for ( int j=0; j<height; ++j,destline+=width )
	{
		for ( int i=0; i<width; ++i )
		{
			if (pixelsToSkip != 0)
			{
				if (pixelsToSkip >= width-i)
				{

					memset( &desPtr[ destline+i ], TRANSPARENT_CODE, width-i);
					pixelsToSkip -= width-i;
					break;
				}
				memset( &desPtr[ destline+i ], TRANSPARENT_CODE, pixelsToSkip);
				i += pixelsToSkip;
				pixelsToSkip = 0;
			}
			al = ((unsigned char*)srcPtr)[ esi++ ];
			if (al < MIN_TRANSPARENT_CODE)
			{
				((unsigned char*)desPtr)[ destline + i ] = al;
			}
			else
			{
				((unsigned char*)desPtr)[ destline + i ] = TRANSPARENT_CODE;
				if (al == MANY_TRANSPARENT_CODE)
				{
					pixelsToSkip = ((unsigned char*)srcPtr)[ esi++ ] -1;
				}
				else
				{
					pixelsToSkip = 256 - al -1;
				}
			}
		}
	}
}
