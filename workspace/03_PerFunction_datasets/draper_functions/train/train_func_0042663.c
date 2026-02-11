fimc_is_cpu_set_power(struct fimc_is *is, int on)
{
	unsigned int timeout = FIMC_IS_POWER_ON_TIMEOUT;

	if (on) {

		mcuctl_write(0, is, REG_WDT_ISP);


		mcuctl_write(is->memory.paddr, is, MCUCTL_REG_BBOAR);


		pmuisp_write(0x18000, is, REG_PMU_ISP_ARM_OPTION);
		pmuisp_write(0x1, is, REG_PMU_ISP_ARM_CONFIGURATION);
	} else {

		pmuisp_write(0x10000, is, REG_PMU_ISP_ARM_OPTION);
		pmuisp_write(0x0, is, REG_PMU_ISP_ARM_CONFIGURATION);

		while (pmuisp_read(is, REG_PMU_ISP_ARM_STATUS) & 1) {
			if (timeout == 0)
				return -ETIME;
			timeout--;
			udelay(1);
		}
	}

	return 0;
}
