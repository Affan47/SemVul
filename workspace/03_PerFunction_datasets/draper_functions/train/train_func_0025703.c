bdc_set_test_mode(struct bdc *bdc)
{
	u32 usb2_pm;

	usb2_pm = bdc_readl(bdc->regs, BDC_USPPM2);
	usb2_pm &= ~BDC_PTC_MASK;
	dev_dbg(bdc->dev, "%s\n", __func__);
	switch (bdc->test_mode) {
	case TEST_J:
	case TEST_K:
	case TEST_SE0_NAK:
	case TEST_PACKET:
	case TEST_FORCE_EN:
		usb2_pm |= bdc->test_mode << 28;
		break;
	default:
		return -EINVAL;
	}
	dev_dbg(bdc->dev, "usb2_pm=%08x", usb2_pm);
	bdc_writel(bdc->regs, BDC_USPPM2, usb2_pm);

	return 0;
}
