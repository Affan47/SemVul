bfa_ioc_ct2_pll_init(void __iomem *rb, enum bfi_asic_mode mode)
{
	u32 wgn, r32, nfc_ver;

	wgn = readl(rb + CT2_WGN_STATUS);

	if (wgn == (__WGN_READY | __GLBL_PF_VF_CFG_RDY)) {


		bfa_ioc_ct2_clk_reset(rb);
		bfa_ioc_ct2_enable_flash(rb);

		bfa_ioc_ct2_mac_reset(rb);

		bfa_ioc_ct2_clk_reset(rb);
		bfa_ioc_ct2_enable_flash(rb);

	} else {
		nfc_ver = readl(rb + CT2_RSC_GPR15_REG);

		if ((nfc_ver >= CT2_NFC_VER_VALID) &&
		    (wgn == (__A2T_AHB_LOAD | __WGN_READY))) {

			bfa_ioc_ct2_wait_till_nfc_running(rb);

			bfa_ioc_ct2_nfc_clk_reset(rb);
		} else {
			bfa_ioc_ct2_nfc_halt(rb);

			bfa_ioc_ct2_clk_reset(rb);
			bfa_ioc_ct2_mac_reset(rb);
			bfa_ioc_ct2_clk_reset(rb);

		}
	}


	r32 = readl(rb + CT2_CHIP_MISC_PRG);
	writel((r32 & 0xfbffffff), (rb + CT2_CHIP_MISC_PRG));


	writel(1, (rb + CT2_LPU0_HOSTFN_MBOX0_MSK));
	writel(1, (rb + CT2_LPU1_HOSTFN_MBOX0_MSK));


	r32 = readl(rb + HOST_SEM5_REG);
	if (r32 & 0x1) {
		r32 = readl((rb + CT2_LPU0_HOSTFN_CMD_STAT));
		if (r32 == 1) {
			writel(1, (rb + CT2_LPU0_HOSTFN_CMD_STAT));
			readl((rb + CT2_LPU0_HOSTFN_CMD_STAT));
		}
		r32 = readl((rb + CT2_LPU1_HOSTFN_CMD_STAT));
		if (r32 == 1) {
			writel(1, (rb + CT2_LPU1_HOSTFN_CMD_STAT));
			readl((rb + CT2_LPU1_HOSTFN_CMD_STAT));
		}
	}

	bfa_ioc_ct2_mem_init(rb);

	writel(BFI_IOC_UNINIT, (rb + CT2_BFA_IOC0_STATE_REG));
	writel(BFI_IOC_UNINIT, (rb + CT2_BFA_IOC1_STATE_REG));

	return BFA_STATUS_OK;
}
