Unpack32Bits( FreeImageIO *io, fi_handle handle, FIBITMAP* dib, MacRect* bounds, WORD rowBytes, int numPlanes ) {
	int height = bounds->bottom - bounds->top;
	int width = bounds->right - bounds->left;

	if (rowBytes == 0) {
		rowBytes = width*4;
	}

	BYTE* pLineBuf = (BYTE*)malloc( rowBytes );
	if ( pLineBuf )	{
		try	{
			for ( int i = 0; i < height; i++ ) {

				int linelen;
				if (rowBytes > 250) {
					linelen = Read16( io, handle );
				} else {
					linelen = Read8( io, handle);
				}

				BYTE* pBuf = UnpackPictRow( io, handle, pLineBuf, width, rowBytes, linelen );


				BYTE* dst = (BYTE*)FreeImage_GetScanLine( dib, height - 1 - i);

				if ( numPlanes == 3 ) {
					for ( int j = 0; j < width; j++ ) {

						dst[ FI_RGBA_BLUE ] = (*(pBuf+width*2));
						dst[ FI_RGBA_GREEN ] = (*(pBuf+width));
						dst[ FI_RGBA_RED ] = (*pBuf);
						dst[ FI_RGBA_ALPHA ] = (0xFF);
						dst += 4;
						pBuf++;
					}
				} else {
					for ( int j = 0; j < width; j++ ) {

						dst[ FI_RGBA_BLUE ] = (*(pBuf+width*3));
						dst[ FI_RGBA_GREEN ] = (*(pBuf+width*2));
						dst[ FI_RGBA_RED ] = (*(pBuf+width));
						dst[ FI_RGBA_ALPHA ] = (*pBuf);
						dst += 4;
						pBuf++;
					}
				}
			}
		}
		catch( ... ) {
			free( pLineBuf );
			throw;
		}
	}
	free( pLineBuf );
}
