ath_pll_reset_ones(struct ath_hal *ah)
{
	static uint8_t reset_pll = 0;

	if(reset_pll == 0) {
#if defined(PROJECT_K2)

		iowrite32(MAGPIE_REG_RST_PWDN_CTRL_ADDR, 0x0);

		iowrite32_mac(0x786c,
			 ioread32_mac(0x786c) | 0x6000000);
		iowrite32_mac(0x786c,
			 ioread32_mac(0x786c) & (~0x6000000));

		iowrite32(MAGPIE_REG_RST_PWDN_CTRL_ADDR, 0x20);

#elif defined(PROJECT_MAGPIE) && !defined (FPGA)
		iowrite32_mac(0x7890,
			 ioread32_mac(0x7890) | 0x1800000);
		iowrite32_mac(0x7890,
			 ioread32_mac(0x7890) & (~0x1800000));
#endif
		reset_pll = 1;
	}
}
