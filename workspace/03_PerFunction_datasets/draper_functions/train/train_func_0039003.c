WriteFile ( LFA_FileRef sourceRef, const std::string & sourcePath )
{
	LFA_FileRef   destRef    = this->parent->fileRef;
	XMP_AbortProc abortProc  = this->parent->abortProc;
	void *        abortArg   = this->parent->abortArg;

	XMP_Int64 fileLen = LFA_Measure ( sourceRef );
	if ( fileLen > 0xFFFFFFFFLL ) {
		XMP_Throw ( "TIFF fles can't exceed 4GB", kXMPErr_BadTIFF );
	}

	LFA_Seek ( sourceRef, 0, SEEK_SET );
	LFA_Truncate ( destRef, 0 );
	LFA_Copy ( sourceRef, destRef, fileLen, abortProc, abortArg );

	this->UpdateFile ( false );

}
