SetClientPacketInfo ( XMP_PacketInfo * clientInfo, const XMP_PacketInfo & handlerInfo,
					  const std::string & xmpPacket, bool needsUpdate )
{

	if ( clientInfo == 0 ) return;

	if ( ! needsUpdate ) {
		*clientInfo = handlerInfo;
	} else {
		clientInfo->offset = kXMPFiles_UnknownOffset;
		clientInfo->length = (XMP_Int32) xmpPacket.size();
		FillPacketInfo ( xmpPacket, clientInfo );
	}

}
