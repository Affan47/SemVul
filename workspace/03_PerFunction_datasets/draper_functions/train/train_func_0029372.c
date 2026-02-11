get_netmask(unsigned long ipaddr)
{
	ipaddr = htonl(ipaddr);

	if ((ipaddr & 0xC0000000) == 0xC0000000)
		return CLASS_C_NETMASK;
	else if ((ipaddr & 0x80000000) == 0x80000000)
		return CLASS_B_NETMASK;
	else if ((ipaddr & 0x80000000) == 0)
		return CLASS_A_NETMASK;
	else
		return 0;
}
