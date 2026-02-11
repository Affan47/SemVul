CheckAtomList ( const LFA_FileRef qtFile, XMP_Int64 spanSize, int nesting )
{
	QTErrorMode status = kBadQT_NoError;
	AtomInfo    info;

	const static XMP_Uns32 moovAtomType = 0x6D6F6F76;
	const static XMP_Uns32 udtaAtomType = 0x75647461;

	for ( ; spanSize >= 8; spanSize -= info.atomSize ) {

		QTErrorMode atomStatus = GetAtomInfo ( qtFile, spanSize, nesting, &info );
		if ( atomStatus != kBadQT_NoError ) return atomStatus;

		XMP_Int64 headerSize = 8;
		if ( info.hasLargeSize ) headerSize = 16;

		if ( (info.atomSize < headerSize) || (info.atomSize > spanSize) ) {
			status = kBadQT_LargeInner;
			if ( nesting == 0 ) status += 2;
			return status;
		}

		bool doChildren = false;
		if ( (nesting == 0) && (info.atomType == moovAtomType) ) doChildren = true;
		if ( (nesting == 1) && (info.atomType == udtaAtomType) ) doChildren = true;

		XMP_Int64 dataSize = info.atomSize - headerSize;

		if ( ! doChildren ) {
			LFA_Seek ( qtFile, dataSize, SEEK_CUR );
		} else {
			QTErrorMode innerStatus = CheckAtomList ( qtFile, dataSize, nesting+1 );
			if ( innerStatus > kBadQT_SmallInner ) return innerStatus;
			if ( status == kBadQT_NoError ) status = innerStatus;
		}

	}

	XMP_Assert ( status <= kBadQT_SmallInner );


	if ( spanSize != 0 ) {
		LFA_Seek ( qtFile, spanSize, SEEK_CUR );
		status = kBadQT_SmallInner;
		if ( spanSize >= 8 ) status = kBadQT_LargeInner;
		if ( nesting == 0 ) status += 2;
	}

	return status;

}
