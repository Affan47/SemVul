sdo_streamon(struct sdo_device *sdev)
{
	int ret;


	sdev->vpll_rate = clk_get_rate(sdev->fout_vpll);
	ret = clk_set_rate(sdev->fout_vpll, 54000000);
	if (ret < 0) {
		dev_err(sdev->dev, "Failed to set vpll rate\n");
		return ret;
	}
	dev_info(sdev->dev, "fout_vpll.rate = %lu\n",
	clk_get_rate(sdev->fout_vpll));

	sdo_write_mask(sdev, SDO_CLKCON, ~0, SDO_TVOUT_CLOCK_ON);
	ret = clk_prepare_enable(sdev->dacphy);
	if (ret < 0) {
		dev_err(sdev->dev, "clk_prepare_enable(dacphy) failed\n");
		goto fail;
	}

	sdo_write_mask(sdev, SDO_DAC, ~0, SDO_POWER_ON_DAC);
	sdo_reg_debug(sdev);
	return 0;

fail:
	sdo_write_mask(sdev, SDO_CLKCON, 0, SDO_TVOUT_CLOCK_ON);
	clk_set_rate(sdev->fout_vpll, sdev->vpll_rate);
	return ret;
}
