OnNonceRequest(Packet *packet)
{
	RakNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID)*2);

	char nonce[TWO_WAY_AUTHENTICATION_NONCE_LENGTH];
	unsigned short requestId;
	nonceGenerator.GetNonce(nonce,&requestId,packet);

	RakNet::BitStream bsOut;
	bsOut.Write((MessageID)ID_TWO_WAY_AUTHENTICATION_NEGOTIATION);
	bsOut.Write((MessageID)ID_NONCE_REPLY);
	bsOut.Write(requestId);
	bsOut.WriteAlignedBytes((const unsigned char*) nonce,TWO_WAY_AUTHENTICATION_NONCE_LENGTH);
	SendUnified(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,packet,false);
}
