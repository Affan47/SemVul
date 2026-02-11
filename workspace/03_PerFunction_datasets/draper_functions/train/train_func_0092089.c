ep0_xsf_complete(struct bdc *bdc, struct bdc_sr *sreport)
{
	dev_dbg(bdc->dev, "%s\n", __func__);
	switch (bdc->ep0_state) {
	case WAIT_FOR_DATA_XMIT:
		bdc->ep0_state = WAIT_FOR_STATUS_START;
		break;
	case WAIT_FOR_STATUS_XMIT:
		bdc->ep0_state = WAIT_FOR_SETUP;
		if (bdc->test_mode) {
			int ret;

			dev_dbg(bdc->dev, "test_mode:%d\n", bdc->test_mode);
			ret = bdc_set_test_mode(bdc);
			if (ret < 0) {
				dev_err(bdc->dev, "Err in setting Test mode\n");
				return;
			}
			bdc->test_mode = 0;
		}
		break;
	case STATUS_PENDING:
		bdc_xsf_ep0_status_start(bdc, sreport);
		break;

	default:
		dev_err(bdc->dev,
			"Unknown ep0_state:%s\n",
			ep0_state_string[bdc->ep0_state]);

	}
}
