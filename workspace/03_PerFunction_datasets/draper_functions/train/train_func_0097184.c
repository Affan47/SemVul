IMGjoinTrans(char* imageBuf, int imgPitch, char* backBuf, int backPitch, int x, int y, char* bitmapPtr)
{
	int destline = y * imgPitch + x;
	int backline = y * backPitch + x;
	int width = ((unsigned char*)bitmapPtr)[0] + (((unsigned char*)bitmapPtr)[1]<<8);
	int height = ((unsigned char*)bitmapPtr)[2] + (((unsigned char*)bitmapPtr)[3]<<8);
	int srcline = 4;
	int al;

	for ( int j=0; j<height; ++j, destline+=imgPitch, backline+=backPitch, srcline+=width )
	{
		for ( int i=0; i<width; ++i )
		{
			al = ((unsigned char*)bitmapPtr)[ srcline + i ];
			if (al == TRANSPARENT_CODE)
			{
				imageBuf[ destline + i ] = backBuf[ backline + i ];
			}
			else
			{
				imageBuf[ destline + i ] = al;
			}
		}
	}
}
