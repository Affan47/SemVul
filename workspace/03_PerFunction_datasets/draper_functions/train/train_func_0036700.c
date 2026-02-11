tscadc_resume(struct device *dev)
{
	struct ti_tscadc_dev	*tscadc_dev = dev_get_drvdata(dev);
	u32 ctrl;

	pm_runtime_get_sync(dev);


	ctrl = CNTRLREG_STEPCONFIGWRT |	CNTRLREG_STEPID;
	tscadc_writel(tscadc_dev, REG_CTRL, ctrl);

	if (tscadc_dev->tsc_cell != -1) {
		if (tscadc_dev->tsc_wires == 5)
			ctrl |= CNTRLREG_5WIRE | CNTRLREG_TSCENB;
		else
			ctrl |= CNTRLREG_4WIRE | CNTRLREG_TSCENB;
		tscadc_idle_config(tscadc_dev);
	}
	ctrl |= CNTRLREG_TSCSSENB;
	tscadc_writel(tscadc_dev, REG_CTRL, ctrl);

	tscadc_writel(tscadc_dev, REG_CLKDIV, tscadc_dev->clk_div);

	return 0;
}
