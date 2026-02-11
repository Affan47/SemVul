IsLegacyChanged()
{

	if ( ! this->changed ) return false;
	if ( this->legacyDeleted ) return true;

	for ( int ifd = 0; ifd < kTIFF_KnownIFDCount; ++ifd ) {

		InternalIFDInfo & thisIFD = this->containedIFDs[ifd];
		if ( ! thisIFD.changed ) continue;

		InternalTagMap::iterator tagPos;
		InternalTagMap::iterator tagEnd = thisIFD.tagMap.end();

		for ( tagPos = thisIFD.tagMap.begin(); tagPos != tagEnd; ++tagPos ) {
			InternalTagInfo & thisTag = tagPos->second;
			if ( thisTag.changed && (thisTag.id != kTIFF_XMP) ) return true;
		}

	}

	return false;

}
