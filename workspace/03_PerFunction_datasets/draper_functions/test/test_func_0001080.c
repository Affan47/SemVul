dgap_do_fep_load(struct board_t *brd, const u8 *ufep, int len)
{
	u8 __iomem *addr;
	uint offset;

	if (!brd || (brd->magic != DGAP_BOARD_MAGIC) || !brd->re_map_membase)
		return;

	addr = brd->re_map_membase;


	offset = 0x1000;
	memcpy_toio(addr + offset, ufep, len);


	if ((brd->type == PCX) || (brd->type == PEPC)) {
		u8 string[100];
		u8 __iomem *config;
		u8 *xconfig;
		unsigned int i = 0;

		xconfig = dgap_create_config_string(brd, string);


		config = addr + CONFIG;
		for (; i < CONFIGSIZE; i++, config++, xconfig++) {
			writeb(*xconfig, config);
			if ((*xconfig & 0xff) == 0xff)
				break;
		}
	}

	writel(0xbfc01004, (addr + 0xc34));
	writel(0x3, (addr + 0xc30));
}
