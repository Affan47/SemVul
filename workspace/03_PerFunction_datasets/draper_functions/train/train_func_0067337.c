GetBoxInfo ( const XMP_Uns8 * boxPtr, const XMP_Uns8 * boxLimit,
							  BoxInfo * info, bool throwErrors  )
{
	XMP_Uns32 u32Size;

	if ( info == 0 ) info = &voidInfo;
	info->boxType = info->headerSize = 0;
	info->contentSize = 0;

	if ( boxPtr >= boxLimit ) XMP_Throw ( "Bad offset to GetBoxInfo", kXMPErr_InternalFailure );

	if ( (boxLimit - boxPtr) < 8 ) {
		if ( throwErrors ) XMP_Throw ( "No space for ISO box header", kXMPErr_BadFileFormat );
		info->headerSize = (XMP_Uns32) (boxLimit - boxPtr);
		return boxLimit;
	}

	u32Size = GetUns32BE ( boxPtr );
	info->boxType = GetUns32BE ( boxPtr+4 );

	if ( u32Size >= 8 ) {
		info->headerSize  = 8;
		info->contentSize = u32Size - 8;
	} else if ( u32Size == 0 ) {
		info->headerSize  = 8;
		info->contentSize = (boxLimit - boxPtr) - 8;
	} else if ( u32Size != 1 ) {
		if ( throwErrors ) XMP_Throw ( "Bad ISO box size, 2..7", kXMPErr_BadFileFormat );
		info->headerSize  = 8;
		info->contentSize = 0;
	} else {
		if ( (boxLimit - boxPtr) < 16 ) {
			if ( throwErrors ) XMP_Throw ( "No space for ISO extended header", kXMPErr_BadFileFormat );
			info->headerSize = (XMP_Uns32) (boxLimit - boxPtr);
			return boxLimit;
		}
		XMP_Uns64 u64Size = GetUns64BE ( boxPtr+8 );
		if ( u64Size < 16 ) {
			if ( throwErrors ) XMP_Throw ( "Bad ISO extended box size, < 16", kXMPErr_BadFileFormat );
			u64Size = 16;
		}
		info->headerSize  = 16;
		info->contentSize = u64Size - 16;
	}

	XMP_Assert ( (XMP_Uns64)(boxLimit - boxPtr) >= (XMP_Uns64)info->headerSize );
	if ( info->contentSize > (XMP_Uns64)((boxLimit - boxPtr) - info->headerSize) ) {
		if ( throwErrors ) XMP_Throw ( "Bad ISO box content size", kXMPErr_BadFileFormat );
		info->contentSize = ((boxLimit - boxPtr) - info->headerSize);
	}

	return (boxPtr + info->headerSize + info->contentSize);

}
