ixgbe_dcb_config_tx_desc_arbiter_82598(struct ixgbe_hw *hw,
						u16 *refill,
						u16 *max,
						u8 *bwg_id,
						u8 *prio_type)
{
	u32    reg, max_credits;
	u8     i;

	reg = IXGBE_READ_REG(hw, IXGBE_DPMCS);


	reg &= ~IXGBE_DPMCS_ARBDIS;
	reg |= IXGBE_DPMCS_TSOEF;


	reg |= (0x4 << IXGBE_DPMCS_MTSOS_SHIFT);

	IXGBE_WRITE_REG(hw, IXGBE_DPMCS, reg);


	for (i = 0; i < MAX_TRAFFIC_CLASS; i++) {
		max_credits = max[i];
		reg = max_credits << IXGBE_TDTQ2TCCR_MCL_SHIFT;
		reg |= refill[i];
		reg |= (u32)(bwg_id[i]) << IXGBE_TDTQ2TCCR_BWG_SHIFT;

		if (prio_type[i] == prio_group)
			reg |= IXGBE_TDTQ2TCCR_GSP;

		if (prio_type[i] == prio_link)
			reg |= IXGBE_TDTQ2TCCR_LSP;

		IXGBE_WRITE_REG(hw, IXGBE_TDTQ2TCCR(i), reg);
	}

	return 0;
}
