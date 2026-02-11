ixgbe_fdir_add_signature_filter_82599(struct ixgbe_hw *hw,
					  union ixgbe_atr_hash_dword input,
					  union ixgbe_atr_hash_dword common,
					  u8 queue)
{
	u64 fdirhashcmd;
	u8 flow_type;
	bool tunnel;
	u32 fdircmd;


	tunnel = !!(input.formatted.flow_type & IXGBE_ATR_L4TYPE_TUNNEL_MASK);
	flow_type = input.formatted.flow_type &
		    (IXGBE_ATR_L4TYPE_TUNNEL_MASK - 1);
	switch (flow_type) {
	case IXGBE_ATR_FLOW_TYPE_TCPV4:
	case IXGBE_ATR_FLOW_TYPE_UDPV4:
	case IXGBE_ATR_FLOW_TYPE_SCTPV4:
	case IXGBE_ATR_FLOW_TYPE_TCPV6:
	case IXGBE_ATR_FLOW_TYPE_UDPV6:
	case IXGBE_ATR_FLOW_TYPE_SCTPV6:
		break;
	default:
		hw_dbg(hw, " Error on flow type input\n");
		return IXGBE_ERR_CONFIG;
	}


	fdircmd = IXGBE_FDIRCMD_CMD_ADD_FLOW | IXGBE_FDIRCMD_FILTER_UPDATE |
		  IXGBE_FDIRCMD_LAST | IXGBE_FDIRCMD_QUEUE_EN;
	fdircmd |= (u32)flow_type << IXGBE_FDIRCMD_FLOW_TYPE_SHIFT;
	fdircmd |= (u32)queue << IXGBE_FDIRCMD_RX_QUEUE_SHIFT;
	if (tunnel)
		fdircmd |= IXGBE_FDIRCMD_TUNNEL_FILTER;


	fdirhashcmd = (u64)fdircmd << 32;
	fdirhashcmd |= ixgbe_atr_compute_sig_hash_82599(input, common);
	IXGBE_WRITE_REG64(hw, IXGBE_FDIRHASH, fdirhashcmd);

	hw_dbg(hw, "Tx Queue=%x hash=%x\n", queue, (u32)fdirhashcmd);

	return 0;
}
