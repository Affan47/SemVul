convertTo24Bits() {
	if(_dib) {
		FIBITMAP *dibRGB = FreeImage_ConvertTo24Bits(_dib);
		return replace(dibRGB);
	}
	return FALSE;
}
