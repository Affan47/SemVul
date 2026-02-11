IMGbltAreaTransRemap(char* imageBuf, int pitch, int desX, int desY, char* bitmapBuf, int srcX1, int srcY1, int srcX2, int srcY2, char*colorTable)
{
	int destline = (desY+srcY1)*pitch + (desX+srcX1);
	int bitmapWidth = ((unsigned char*)bitmapBuf)[0] + (((unsigned char*)bitmapBuf)[1]<<8);

	int width = srcX2 - srcX1 + 1;
	int height = srcY2 - srcY1 + 1;
	int esi = 4 + srcY1 * bitmapWidth + srcX1;

	for ( int j=0; j<height; ++j,destline+=pitch,esi+=bitmapWidth )
	{
		for ( int i=0; i<width; ++i )
		{
			if ( ((unsigned char*)bitmapBuf)[esi + i] != TRANSPARENT_CODE)
			{
				imageBuf[destline + i] = colorTable[ bitmapBuf[esi+i] ];
			}
		}
	}
}
