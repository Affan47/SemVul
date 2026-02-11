GetTag_Double ( XMP_Uns8 ifd, XMP_Uns16 id, double* data ) const
{
	const InternalTagInfo* thisTag = this->FindTagInIFD ( ifd, id );
	if ( (thisTag == 0) || (thisTag->dataPtr == 0) ) return false;
	if ( (thisTag->type != kTIFF_DoubleType) || (thisTag->dataLen != 8) ) return false;

	if ( data != 0 ) *data = this->GetDouble ( thisTag->dataPtr );
	return true;

}
