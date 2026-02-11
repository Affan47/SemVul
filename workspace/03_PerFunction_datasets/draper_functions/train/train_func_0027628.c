rts524a_read_phy(struct rtsx_pcr *pcr, u8 addr, u16 *val)
{
	addr = addr & 0x80 ? (addr & 0x7F) | 0x40 : addr;

	return __rtsx_pci_read_phy_register(pcr, addr, val);
}
