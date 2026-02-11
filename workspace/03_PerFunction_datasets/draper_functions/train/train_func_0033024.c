dwc2_hsotg_set_test_mode(struct dwc2_hsotg *hsotg, int testmode)
{
	int dctl = dwc2_readl(hsotg->regs + DCTL);

	dctl &= ~DCTL_TSTCTL_MASK;
	switch (testmode) {
	case TEST_J:
	case TEST_K:
	case TEST_SE0_NAK:
	case TEST_PACKET:
	case TEST_FORCE_EN:
		dctl |= testmode << DCTL_TSTCTL_SHIFT;
		break;
	default:
		return -EINVAL;
	}
	dwc2_writel(dctl, hsotg->regs + DCTL);
	return 0;
}
