PushNewHost(const RakNetGUID &guid, RakNetGUID oldHost)
{
	Packet *p = AllocatePacketUnified(sizeof(MessageID)+sizeof(oldHost));
	RakNet::BitStream bs(p->data,p->length,false);
	bs.SetWriteOffset(0);
	bs.Write((MessageID)ID_FCM2_NEW_HOST);
	bs.Write(oldHost);
	p->systemAddress=rakPeerInterface->GetSystemAddressFromGuid(guid);
	p->systemAddress.systemIndex=(SystemIndex)-1;
	p->guid=guid;
	p->wasGeneratedLocally=true;
	rakPeerInterface->PushBackPacket(p, true);

	lastPushedHost=guid;
}
