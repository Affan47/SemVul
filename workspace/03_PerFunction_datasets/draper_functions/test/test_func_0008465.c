ixgbe_write_iosf_sb_reg_x550(struct ixgbe_hw *hw, u32 reg_addr,
					u32 device_type, u32 data)
{
	u32 gssr = IXGBE_GSSR_PHY1_SM | IXGBE_GSSR_PHY0_SM;
	u32 command, error;
	s32 ret;

	ret = hw->mac.ops.acquire_swfw_sync(hw, gssr);
	if (ret)
		return ret;

	ret = ixgbe_iosf_wait(hw, NULL);
	if (ret)
		goto out;

	command = ((reg_addr << IXGBE_SB_IOSF_CTRL_ADDR_SHIFT) |
		   (device_type << IXGBE_SB_IOSF_CTRL_TARGET_SELECT_SHIFT));


	IXGBE_WRITE_REG(hw, IXGBE_SB_IOSF_INDIRECT_CTRL, command);


	IXGBE_WRITE_REG(hw, IXGBE_SB_IOSF_INDIRECT_DATA, data);

	ret = ixgbe_iosf_wait(hw, &command);

	if ((command & IXGBE_SB_IOSF_CTRL_RESP_STAT_MASK) != 0) {
		error = (command & IXGBE_SB_IOSF_CTRL_CMPL_ERR_MASK) >>
			 IXGBE_SB_IOSF_CTRL_CMPL_ERR_SHIFT;
		hw_dbg(hw, "Failed to write, error %x\n", error);
		return IXGBE_ERR_PHY;
	}

out:
	hw->mac.ops.release_swfw_sync(hw, gssr);
	return ret;
}
