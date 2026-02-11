read_paged_phy_reg(struct fw_ohci *ohci, int page, int addr)
{
	int ret;

	ret = update_phy_reg(ohci, 7, PHY_PAGE_SELECT, page << 5);
	if (ret < 0)
		return ret;

	return read_phy_reg(ohci, addr);
}
