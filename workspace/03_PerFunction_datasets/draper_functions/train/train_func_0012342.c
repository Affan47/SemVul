ixgbe_set_rxpba_generic(struct ixgbe_hw *hw,
			     int num_pb,
			     u32 headroom,
			     int strategy)
{
	u32 pbsize = hw->mac.rx_pb_size;
	int i = 0;
	u32 rxpktsize, txpktsize, txpbthresh;


	pbsize -= headroom;

	if (!num_pb)
		num_pb = 1;


	switch (strategy) {
	case (PBA_STRATEGY_WEIGHTED):


		rxpktsize = ((pbsize * 5 * 2) / (num_pb * 8));
		pbsize -= rxpktsize * (num_pb / 2);
		rxpktsize <<= IXGBE_RXPBSIZE_SHIFT;
		for (; i < (num_pb / 2); i++)
			IXGBE_WRITE_REG(hw, IXGBE_RXPBSIZE(i), rxpktsize);

	case (PBA_STRATEGY_EQUAL):

		rxpktsize = (pbsize / (num_pb - i)) << IXGBE_RXPBSIZE_SHIFT;
		for (; i < num_pb; i++)
			IXGBE_WRITE_REG(hw, IXGBE_RXPBSIZE(i), rxpktsize);
		break;
	default:
		break;
	}


	txpktsize = IXGBE_TXPBSIZE_MAX / num_pb;
	txpbthresh = (txpktsize / 1024) - IXGBE_TXPKT_SIZE_MAX;
	for (i = 0; i < num_pb; i++) {
		IXGBE_WRITE_REG(hw, IXGBE_TXPBSIZE(i), txpktsize);
		IXGBE_WRITE_REG(hw, IXGBE_TXPBTHRESH(i), txpbthresh);
	}


	for (; i < IXGBE_MAX_PB; i++) {
		IXGBE_WRITE_REG(hw, IXGBE_RXPBSIZE(i), 0);
		IXGBE_WRITE_REG(hw, IXGBE_TXPBSIZE(i), 0);
		IXGBE_WRITE_REG(hw, IXGBE_TXPBTHRESH(i), 0);
	}
}
