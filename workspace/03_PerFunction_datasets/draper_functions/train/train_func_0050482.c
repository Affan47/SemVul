ixgbevf_write_msg_read_ack(struct ixgbe_hw *hw,
				       u32 *msg, u16 size)
{
	struct ixgbe_mbx_info *mbx = &hw->mbx;
	u32 retmsg[IXGBE_VFMAILBOX_SIZE];
	s32 retval = mbx->ops.write_posted(hw, msg, size);

	if (!retval)
		mbx->ops.read_posted(hw, retmsg, size);
}
