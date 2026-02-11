threshold(BYTE T) {
	if(_dib) {
		FIBITMAP *dib1 = FreeImage_Threshold(_dib, T);
		return replace(dib1);
	}
	return FALSE;
}
