DumpScriptDataTagContent ( LFA_FileRef file, XMP_Uns32 sdOffset, XMP_Uns32 tagTime )
{
	XMP_Uns8 buffer [64*1024];
	size_t   ioCount;

	LFA_Seek ( file, sdOffset, SEEK_SET );
	ioCount = LFA_Read ( file, buffer, 3, true );
	if ( (ioCount != 3) || (buffer[0] != 2) ) {
		tree->comment ( "** Failure reading ScriptDataObject start, ioCount = %d, buffer[0]=0x%X", ioCount, buffer[0] );
		return (sdOffset + ioCount);
	}

	XMP_Uns16 nameLen = GetUns16BE ( &buffer[1] );
	ioCount = LFA_Read ( file, buffer, nameLen, true );
	if ( ioCount != nameLen ) {
		tree->comment ( "** Failure reading ScriptDataObject name, ioCount = %d", ioCount );
		return (sdOffset + 3 + ioCount);
	}

	tree->addComment ( "%.*s @ 0x%X", nameLen, buffer, sdOffset );
	if ( buffer[nameLen-1] == 0 ) tree->addComment ( "name has trailing nul" );

	bool isOnXMP = (tagTime == 0) && (nameLen == 9) && (strncmp ( (char*)buffer, "onXMPData", 9 ) == 0);
	return DumpScriptDataValue ( file, (sdOffset+1+2+nameLen), isOnXMP );

}
