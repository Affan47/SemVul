csio_wr_get_sge(struct csio_hw *hw)
{
	struct csio_wrm *wrm = csio_hw_to_wrm(hw);
	struct csio_sge *sge = &wrm->sge;
	uint32_t ingpad;
	int i;
	u32 timer_value_0_and_1, timer_value_2_and_3, timer_value_4_and_5;
	u32 ingress_rx_threshold;

	sge->sge_control = csio_rd_reg32(hw, SGE_CONTROL_A);

	ingpad = INGPADBOUNDARY_G(sge->sge_control);

	switch (ingpad) {
	case X_INGPCIEBOUNDARY_32B:
		sge->csio_fl_align = 32; break;
	case X_INGPCIEBOUNDARY_64B:
		sge->csio_fl_align = 64; break;
	case X_INGPCIEBOUNDARY_128B:
		sge->csio_fl_align = 128; break;
	case X_INGPCIEBOUNDARY_256B:
		sge->csio_fl_align = 256; break;
	case X_INGPCIEBOUNDARY_512B:
		sge->csio_fl_align = 512; break;
	case X_INGPCIEBOUNDARY_1024B:
		sge->csio_fl_align = 1024; break;
	case X_INGPCIEBOUNDARY_2048B:
		sge->csio_fl_align = 2048; break;
	case X_INGPCIEBOUNDARY_4096B:
		sge->csio_fl_align = 4096; break;
	}

	for (i = 0; i < CSIO_SGE_FL_SIZE_REGS; i++)
		csio_get_flbuf_size(hw, sge, i);

	timer_value_0_and_1 = csio_rd_reg32(hw, SGE_TIMER_VALUE_0_AND_1_A);
	timer_value_2_and_3 = csio_rd_reg32(hw, SGE_TIMER_VALUE_2_AND_3_A);
	timer_value_4_and_5 = csio_rd_reg32(hw, SGE_TIMER_VALUE_4_AND_5_A);

	sge->timer_val[0] = (uint16_t)csio_core_ticks_to_us(hw,
					TIMERVALUE0_G(timer_value_0_and_1));
	sge->timer_val[1] = (uint16_t)csio_core_ticks_to_us(hw,
					TIMERVALUE1_G(timer_value_0_and_1));
	sge->timer_val[2] = (uint16_t)csio_core_ticks_to_us(hw,
					TIMERVALUE2_G(timer_value_2_and_3));
	sge->timer_val[3] = (uint16_t)csio_core_ticks_to_us(hw,
					TIMERVALUE3_G(timer_value_2_and_3));
	sge->timer_val[4] = (uint16_t)csio_core_ticks_to_us(hw,
					TIMERVALUE4_G(timer_value_4_and_5));
	sge->timer_val[5] = (uint16_t)csio_core_ticks_to_us(hw,
					TIMERVALUE5_G(timer_value_4_and_5));

	ingress_rx_threshold = csio_rd_reg32(hw, SGE_INGRESS_RX_THRESHOLD_A);
	sge->counter_val[0] = THRESHOLD_0_G(ingress_rx_threshold);
	sge->counter_val[1] = THRESHOLD_1_G(ingress_rx_threshold);
	sge->counter_val[2] = THRESHOLD_2_G(ingress_rx_threshold);
	sge->counter_val[3] = THRESHOLD_3_G(ingress_rx_threshold);

	csio_init_intr_coalesce_parms(hw);
}
