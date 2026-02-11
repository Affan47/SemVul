BootstrapKad(uint32 ip, uint16 port)
{
	if (!Kademlia::CKademlia::IsRunning()) {
		Kademlia::CKademlia::Start();
		theApp->ShowConnectionState();
	}

	Kademlia::CKademlia::Bootstrap(ip, port);
}
