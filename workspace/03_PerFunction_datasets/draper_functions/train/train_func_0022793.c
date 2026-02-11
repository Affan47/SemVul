LFA_Measure ( LFA_FileRef file )
	{
		int descr = (int)file;

		off_t currPos = lseek ( descr, 0, SEEK_CUR );
		off_t length  = lseek ( descr, 0, SEEK_END );
		if ( (currPos == -1) || (length == -1) ) LFA_Throw ( "LFA_Measure: lseek failure", kLFAErr_ExternalFailure );
		(void) lseek ( descr, currPos, SEEK_SET );

		return length;

	}
