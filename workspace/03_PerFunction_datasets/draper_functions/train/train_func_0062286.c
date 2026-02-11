FreeImage_GetICCProfile(FIBITMAP *dib) {
	FIICCPROFILE *profile = (dib) ? (FIICCPROFILE *)&((FREEIMAGEHEADER *)dib->data)->iccProfile : NULL;
	return profile;
}
