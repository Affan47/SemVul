ProcessXMP()
{

	if ( (!this->containsXMP) || this->processedXMP ) return;

	if ( this->handlerFlags & kXMPFiles_CanReconcile ) {
		XMP_Throw ( "Reconciling file handlers must implement ProcessXMP", kXMPErr_InternalFailure );
	}

	SXMPUtils::RemoveProperties ( &this->xmpObj, 0, 0, kXMPUtil_DoAllProperties );
	this->xmpObj.ParseFromBuffer ( this->xmpPacket.c_str(), (XMP_StringLen)this->xmpPacket.size() );
	this->processedXMP = true;

}
