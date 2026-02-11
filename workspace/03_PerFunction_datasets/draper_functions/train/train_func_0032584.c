GetID() const {
	uint32 ID;

	if( Kademlia::CKademlia::IsConnected() && !Kademlia::CKademlia::IsFirewalled() ) {

		ID = ENDIAN_NTOHL(Kademlia::CKademlia::GetIPAddress());
	} else if( theApp->serverconnect->IsConnected() ) {
		ID = theApp->serverconnect->GetClientID();
	} else if ( Kademlia::CKademlia::IsConnected() && Kademlia::CKademlia::IsFirewalled() ) {

		ID = 1;
	} else {
		ID = 0;
	}

	return ID;
}
