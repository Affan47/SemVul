ixgbe_update_vf_xcast_mode(struct ixgbe_adapter *adapter,
				      u32 *msgbuf, u32 vf)
{
	struct ixgbe_hw *hw = &adapter->hw;
	int xcast_mode = msgbuf[1];
	u32 vmolr, disable, enable;


	switch (adapter->vfinfo[vf].vf_api) {
	case ixgbe_mbox_api_12:
		break;
	default:
		return -EOPNOTSUPP;
	}

	if (xcast_mode > IXGBEVF_XCAST_MODE_MULTI &&
	    !adapter->vfinfo[vf].trusted) {
		xcast_mode = IXGBEVF_XCAST_MODE_MULTI;
	}

	if (adapter->vfinfo[vf].xcast_mode == xcast_mode)
		goto out;

	switch (xcast_mode) {
	case IXGBEVF_XCAST_MODE_NONE:
		disable = IXGBE_VMOLR_BAM | IXGBE_VMOLR_ROMPE | IXGBE_VMOLR_MPE;
		enable = 0;
		break;
	case IXGBEVF_XCAST_MODE_MULTI:
		disable = IXGBE_VMOLR_MPE;
		enable = IXGBE_VMOLR_BAM | IXGBE_VMOLR_ROMPE;
		break;
	case IXGBEVF_XCAST_MODE_ALLMULTI:
		disable = 0;
		enable = IXGBE_VMOLR_BAM | IXGBE_VMOLR_ROMPE | IXGBE_VMOLR_MPE;
		break;
	default:
		return -EOPNOTSUPP;
	}

	vmolr = IXGBE_READ_REG(hw, IXGBE_VMOLR(vf));
	vmolr &= ~disable;
	vmolr |= enable;
	IXGBE_WRITE_REG(hw, IXGBE_VMOLR(vf), vmolr);

	adapter->vfinfo[vf].xcast_mode = xcast_mode;

out:
	msgbuf[1] = xcast_mode;

	return 0;
}
