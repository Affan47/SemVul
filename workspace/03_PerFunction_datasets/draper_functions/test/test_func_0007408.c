FlipOECFSFRTable ( void* voidPtr, XMP_Uns32 tagLen, GetUns16_Proc GetUns16 )
{
	XMP_Uns16* u16Ptr = (XMP_Uns16*)voidPtr;

	Flip2 ( &u16Ptr[0] );
	Flip2 ( &u16Ptr[1] );

	XMP_Uns16 columns = GetUns16 ( &u16Ptr[0] );
	XMP_Uns16 rows    = GetUns16 ( &u16Ptr[1] );

	XMP_Uns32 minLen = 4 + columns + (8 * columns * rows);
	if ( tagLen < minLen ) return false;


	XMP_Uns32* u32Ptr = (XMP_Uns32*) ((XMP_Uns8*)voidPtr + tagLen - (8 * columns * rows));

	for ( size_t i = 2*columns*rows; i > 0; --i, ++u32Ptr ) Flip4 ( u32Ptr );

	return true;

}
