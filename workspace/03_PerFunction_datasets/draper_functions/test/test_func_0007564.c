intel_soc_thermal_exit(void)
{
	if (soc_dts_thres_irq)
		free_irq(soc_dts_thres_irq, soc_dts);
	intel_soc_dts_iosf_exit(soc_dts);
}
