e1000_write_phy_reg(struct e1000_hw *hw, u32 reg_addr, u16 phy_data)
{
	u32 ret_val;
	unsigned long flags;

	spin_lock_irqsave(&e1000_phy_lock, flags);

	if ((hw->phy_type == e1000_phy_igp) &&
	    (reg_addr > MAX_PHY_MULTI_PAGE_REG)) {
		ret_val = e1000_write_phy_reg_ex(hw, IGP01E1000_PHY_PAGE_SELECT,
						 (u16)reg_addr);
		if (ret_val) {
			spin_unlock_irqrestore(&e1000_phy_lock, flags);
			return ret_val;
		}
	}

	ret_val = e1000_write_phy_reg_ex(hw, MAX_PHY_REG_ADDRESS & reg_addr,
					 phy_data);
	spin_unlock_irqrestore(&e1000_phy_lock, flags);

	return ret_val;
}
