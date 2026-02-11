LFA_Write ( LFA_FileRef file, const void * buffer, XMP_Int32 bytes )
	{
		int descr = (int)file;

		ssize_t bytesWritten = write ( descr, buffer, bytes );
		if ( bytesWritten != bytes ) LFA_Throw ( "LFA_Write: write failure", kLFAErr_ExternalFailure );

	}
