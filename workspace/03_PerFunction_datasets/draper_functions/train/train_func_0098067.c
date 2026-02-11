fpi_drvcb_report_verify_result(struct fp_dev *dev, int result,
	struct fp_img *img)
{
	fp_dbg("result %d", result);
	BUG_ON(dev->state != DEV_STATE_VERIFYING);
	if (result < 0 || result == FP_VERIFY_NO_MATCH
			|| result == FP_VERIFY_MATCH)
		dev->state = DEV_STATE_VERIFY_DONE;

	if (dev->verify_cb)
		dev->verify_cb(dev, result, img, dev->verify_cb_data);
	else
		fp_dbg("ignoring verify result as no callback is subscribed");
}
