prot_autoc_write_82599(struct ixgbe_hw *hw, u32 autoc, bool locked)
{
	s32 ret_val = 0;


	if (ixgbe_check_reset_blocked(hw))
		goto out;


	if (!locked && ixgbe_verify_lesm_fw_enabled_82599(hw)) {
		ret_val = hw->mac.ops.acquire_swfw_sync(hw,
					IXGBE_GSSR_MAC_CSR_SM);
		if (ret_val)
			return IXGBE_ERR_SWFW_SYNC;

		locked = true;
	}

	IXGBE_WRITE_REG(hw, IXGBE_AUTOC, autoc);
	ret_val = ixgbe_reset_pipeline_82599(hw);

out:


	if (locked)
		hw->mac.ops.release_swfw_sync(hw, IXGBE_GSSR_MAC_CSR_SM);

	return ret_val;
}
