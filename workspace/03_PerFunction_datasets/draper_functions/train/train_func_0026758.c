tg3_setup_eee(struct tg3 *tp)
{
	u32 val;

	val = TG3_CPMU_EEE_LNKIDL_PCIE_NL0 |
	      TG3_CPMU_EEE_LNKIDL_UART_IDL;
	if (tg3_chip_rev_id(tp) == CHIPREV_ID_57765_A0)
		val |= TG3_CPMU_EEE_LNKIDL_APE_TX_MT;

	tw32_f(TG3_CPMU_EEE_LNKIDL_CTRL, val);

	tw32_f(TG3_CPMU_EEE_CTRL,
	       TG3_CPMU_EEE_CTRL_EXIT_20_1_US);

	val = TG3_CPMU_EEEMD_ERLY_L1_XIT_DET |
	      (tp->eee.tx_lpi_enabled ? TG3_CPMU_EEEMD_LPI_IN_TX : 0) |
	      TG3_CPMU_EEEMD_LPI_IN_RX |
	      TG3_CPMU_EEEMD_EEE_ENABLE;

	if (tg3_asic_rev(tp) != ASIC_REV_5717)
		val |= TG3_CPMU_EEEMD_SND_IDX_DET_EN;

	if (tg3_flag(tp, ENABLE_APE))
		val |= TG3_CPMU_EEEMD_APE_TX_DET_EN;

	tw32_f(TG3_CPMU_EEE_MODE, tp->eee.eee_enabled ? val : 0);

	tw32_f(TG3_CPMU_EEE_DBTMR1,
	       TG3_CPMU_DBTMR1_PCIEXIT_2047US |
	       (tp->eee.tx_lpi_timer & 0xffff));

	tw32_f(TG3_CPMU_EEE_DBTMR2,
	       TG3_CPMU_DBTMR2_APE_TX_2047US |
	       TG3_CPMU_DBTMR2_TXIDXEQ_2047US);
}
