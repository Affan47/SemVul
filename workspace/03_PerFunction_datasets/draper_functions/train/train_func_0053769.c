niu_set_primary_mac(struct niu *np, unsigned char *addr)
{
	u16 reg0 = addr[4] << 8 | addr[5];
	u16 reg1 = addr[2] << 8 | addr[3];
	u16 reg2 = addr[0] << 8 | addr[1];

	if (np->flags & NIU_FLAGS_XMAC) {
		nw64_mac(XMAC_ADDR0, reg0);
		nw64_mac(XMAC_ADDR1, reg1);
		nw64_mac(XMAC_ADDR2, reg2);
	} else {
		nw64_mac(BMAC_ADDR0, reg0);
		nw64_mac(BMAC_ADDR1, reg1);
		nw64_mac(BMAC_ADDR2, reg2);
	}
}
