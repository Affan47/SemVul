CopyTagToMasterIFD ( const TagInfo & ps6Tag, InternalIFDInfo * masterIFD )
{
	InternalTagMap::value_type mapValue ( ps6Tag.id, InternalTagInfo ( ps6Tag.id, ps6Tag.type, ps6Tag.count, this->fileParsed ) );
	InternalTagMap::iterator newPos = masterIFD->tagMap.insert ( masterIFD->tagMap.end(), mapValue );
	InternalTagInfo& newTag = newPos->second;

	newTag.dataLen = ps6Tag.dataLen;

	if ( newTag.dataLen <= 4 ) {
		newTag.dataPtr = (XMP_Uns8*) &newTag.smallValue;
		newTag.smallValue = *((XMP_Uns32*)ps6Tag.dataPtr);
	} else {
		newTag.dataPtr = (XMP_Uns8*) malloc ( newTag.dataLen );
		if ( newTag.dataPtr == 0 ) XMP_Throw ( "Out of memory", kXMPErr_NoMemory );
		memcpy ( newTag.dataPtr, ps6Tag.dataPtr, newTag.dataLen );
	}

	newTag.changed = true;
	XMP_Assert ( (newTag.origDataLen == 0) && (newTag.origDataOffset == 0) );

	masterIFD->changed = true;

	return newPos->second.dataPtr;

}
