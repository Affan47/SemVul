lis302dl_interrupt_handle_click(struct lis3lv02d *lis3)
{
	struct input_dev *dev = lis3->idev->input;
	u8 click_src;

	mutex_lock(&lis3->mutex);
	lis3->read(lis3, CLICK_SRC, &click_src);

	if (click_src & CLICK_SINGLE_X) {
		input_report_key(dev, lis3->mapped_btns[0], 1);
		input_report_key(dev, lis3->mapped_btns[0], 0);
	}

	if (click_src & CLICK_SINGLE_Y) {
		input_report_key(dev, lis3->mapped_btns[1], 1);
		input_report_key(dev, lis3->mapped_btns[1], 0);
	}

	if (click_src & CLICK_SINGLE_Z) {
		input_report_key(dev, lis3->mapped_btns[2], 1);
		input_report_key(dev, lis3->mapped_btns[2], 0);
	}
	input_sync(dev);
	mutex_unlock(&lis3->mutex);
}
