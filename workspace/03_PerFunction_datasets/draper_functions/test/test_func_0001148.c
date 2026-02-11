IsFirewalledKadUDP() const
{
	return !Kademlia::CKademlia::IsConnected()
			|| Kademlia::CUDPFirewallTester::IsFirewalledUDP(true);
}
