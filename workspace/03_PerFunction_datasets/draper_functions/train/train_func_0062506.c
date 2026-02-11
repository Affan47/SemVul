__e1000_read_phy_reg_hv(struct e1000_hw *hw, u32 offset, u16 *data,
				   bool locked, bool page_set)
{
	s32 ret_val;
	u16 page = BM_PHY_REG_PAGE(offset);
	u16 reg = BM_PHY_REG_NUM(offset);
	u32 phy_addr = hw->phy.addr = e1000_get_phy_addr_for_hv_page(page);

	if (!locked) {
		ret_val = hw->phy.ops.acquire(hw);
		if (ret_val)
			return ret_val;
	}


	if (page == BM_WUC_PAGE) {
		ret_val = e1000_access_phy_wakeup_reg_bm(hw, offset, data,
							 true, page_set);
		goto out;
	}

	if (page > 0 && page < HV_INTC_FC_PAGE_START) {
		ret_val = e1000_access_phy_debug_regs_hv(hw, offset,
							 data, true);
		goto out;
	}

	if (!page_set) {
		if (page == HV_INTC_FC_PAGE_START)
			page = 0;

		if (reg > MAX_PHY_MULTI_PAGE_REG) {

			ret_val = e1000_set_page_igp(hw,
						     (page << IGP_PAGE_SHIFT));

			hw->phy.addr = phy_addr;

			if (ret_val)
				goto out;
		}
	}

	e_dbg("reading PHY page %d (or 0x%x shifted) reg 0x%x\n", page,
	      page << IGP_PAGE_SHIFT, reg);

	ret_val = e1000e_read_phy_reg_mdic(hw, MAX_PHY_REG_ADDRESS & reg, data);
out:
	if (!locked)
		hw->phy.ops.release(hw);

	return ret_val;
}
