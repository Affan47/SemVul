ipv4_addr_is_routable(uint32 ip)
{
	static const struct {
		const uint32 addr, mask;
	} net[] = {
		{ 0x00000000UL, 0xff000000UL },
		{ 0xe0000000UL, 0xe0000000UL },
		{ 0x7f000000UL,	0xff000000UL },
		{ 0xc0000200UL, 0xffffff00UL },
		{ 0xc0586300UL, 0xffffff00UL },
		{ 0xc6120000UL, 0xfffe0000UL },
	};
	uint i;

	for (i = 0; i < G_N_ELEMENTS(net); i++) {
		if ((ip & net[i].mask) == net[i].addr)
			return FALSE;
	}

	return TRUE;
}
