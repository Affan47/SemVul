fcoe_wwn_from_mac(unsigned char mac[MAX_ADDR_LEN],
		      unsigned int scheme, unsigned int port)
{
	u64 wwn;
	u64 host_mac;


	host_mac = ((u64) mac[0] << 40) |
		((u64) mac[1] << 32) |
		((u64) mac[2] << 24) |
		((u64) mac[3] << 16) |
		((u64) mac[4] << 8) |
		(u64) mac[5];

	WARN_ON(host_mac >= (1ULL << 48));
	wwn = host_mac | ((u64) scheme << 60);
	switch (scheme) {
	case 1:
		WARN_ON(port != 0);
		break;
	case 2:
		WARN_ON(port >= 0xfff);
		wwn |= (u64) port << 48;
		break;
	default:
		WARN_ON(1);
		break;
	}

	return wwn;
}
