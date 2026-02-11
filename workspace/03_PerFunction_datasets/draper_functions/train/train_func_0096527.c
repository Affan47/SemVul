ixgbevf_poll_for_ack(struct ixgbe_hw *hw)
{
	struct ixgbe_mbx_info *mbx = &hw->mbx;
	int countdown = mbx->timeout;

	while (countdown && mbx->ops.check_for_ack(hw)) {
		countdown--;
		udelay(mbx->udelay);
	}


	if (!countdown)
		mbx->timeout = 0;

	return countdown ? 0 : IXGBE_ERR_MBX;
}
