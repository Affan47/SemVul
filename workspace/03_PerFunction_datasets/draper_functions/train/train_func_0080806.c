init_reqs_cb(struct fp_img_dev *dev, int result, void *user_data)
{
	fpi_imgdev_activate_complete(dev, result);
	if (result == 0)
		do_capture(dev);
}
