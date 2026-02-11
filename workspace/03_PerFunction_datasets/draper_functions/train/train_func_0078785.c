GetBox ( const char * boxPath, BoxInfo * info ) const
{
	size_t pathLen = strlen(boxPath);
	XMP_Assert ( (pathLen >= 4) && XMP_LitNMatch ( boxPath, "moov", 4 ) );
	if ( info != 0 ) memset ( info, 0, sizeof(BoxInfo) );

	const char * pathPtr = boxPath + 5;
	const char * pathEnd = boxPath + pathLen;

	BoxRef currRef = &this->moovNode;

	while ( pathPtr < pathEnd ) {

		XMP_Assert ( (pathEnd - pathPtr) >= 4 );
		XMP_Uns32 boxType = GetUns32BE ( pathPtr );
		pathPtr += 5;

		currRef = this->GetTypeChild ( currRef, boxType, 0 );
		if ( currRef == 0 ) return 0;

	}

	this->FillBoxInfo ( *((BoxNode*)currRef), info );
	return currRef;

}
