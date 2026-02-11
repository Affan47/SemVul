ti_bandgap_suspend(struct device *dev)
{
	struct ti_bandgap *bgp = dev_get_drvdata(dev);
	int err;

	err = ti_bandgap_save_ctxt(bgp);
	ti_bandgap_power(bgp, false);

	if (TI_BANDGAP_HAS(bgp, CLK_CTRL))
		clk_disable_unprepare(bgp->fclock);

	return err;
}
