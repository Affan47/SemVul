Encode2RGBA(CxFile *hFile, bool bFlipY)
{
	if (EncodeSafeCheck(hFile)) return false;

	for (long y1 = head.biHeight-1; y1 > -1; y1--) {
		long y = bFlipY ? head.biHeight - 1 - y1 : y1;
		for(long x = 0; x < head.biWidth; x++) {
			RGBQUAD color = BlindGetPixelColor(x,y);
			hFile->PutC(color.rgbRed);
			hFile->PutC(color.rgbGreen);
			hFile->PutC(color.rgbBlue);
			hFile->PutC(color.rgbReserved);
		}
	}
	return true;
}
