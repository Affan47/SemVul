Process2BootstrapRequest(uint32_t ip, uint16_t port, const CKadUDPKey& senderKey)
{

	ContactList contacts;
	uint16_t numContacts = (uint16_t)CKademlia::GetRoutingZone()->GetBootstrapContacts(&contacts, 20);


	CMemFile packetdata(521);

	packetdata.WriteUInt128(CKademlia::GetPrefs()->GetKadID());
	packetdata.WriteUInt16(thePrefs::GetPort());
	packetdata.WriteUInt8(KADEMLIA_VERSION);


	packetdata.WriteUInt16(numContacts);
	CContact *contact;
	for (ContactList::const_iterator it = contacts.begin(); it != contacts.end(); ++it) {
		contact = *it;
		packetdata.WriteUInt128(contact->GetClientID());
		packetdata.WriteUInt32(contact->GetIPAddress());
		packetdata.WriteUInt16(contact->GetUDPPort());
		packetdata.WriteUInt16(contact->GetTCPPort());
		packetdata.WriteUInt8(contact->GetVersion());
	}


	DebugSend(Kad2BootstrapRes, ip, port);
	SendPacket(packetdata, KADEMLIA2_BOOTSTRAP_RES, ip, port, senderKey, NULL);
}
