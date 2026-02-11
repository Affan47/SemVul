FreeImage_GetInfoHeader(FIBITMAP *dib) {
	if(!dib) return NULL;
	size_t lp = (size_t)dib->data + sizeof(FREEIMAGEHEADER);
	lp += (lp % FIBITMAP_ALIGNMENT ? FIBITMAP_ALIGNMENT - lp % FIBITMAP_ALIGNMENT : 0);
	lp += FIBITMAP_ALIGNMENT - sizeof(BITMAPINFOHEADER) % FIBITMAP_ALIGNMENT;
	return (BITMAPINFOHEADER *)lp;
}
