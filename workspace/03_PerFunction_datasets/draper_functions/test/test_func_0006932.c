readreg(int portno)
{
	outw(portno, eth_nic_base + ADD_PORT);
	return inw(eth_nic_base + DATA_PORT);
}
