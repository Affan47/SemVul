DumpToFile ( void * refCon, XMP_StringPtr outStr, XMP_StringLen outLen )
{
	XMP_Status	status	= 0;
	size_t		count;
	FILE *		outFile	= static_cast < FILE * > ( refCon );

	count = fwrite ( outStr, 1, outLen, outFile );
	if ( count != outLen ) status = errno;
	fflush ( outFile );
	return status;

}
