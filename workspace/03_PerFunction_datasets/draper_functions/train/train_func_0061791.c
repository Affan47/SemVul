wiimod_mp_probe(const struct wiimod_ops *ops,
			   struct wiimote_data *wdata)
{
	int ret;

	wdata->mp = input_allocate_device();
	if (!wdata->mp)
		return -ENOMEM;

	input_set_drvdata(wdata->mp, wdata);
	wdata->mp->open = wiimod_mp_open;
	wdata->mp->close = wiimod_mp_close;
	wdata->mp->dev.parent = &wdata->hdev->dev;
	wdata->mp->id.bustype = wdata->hdev->bus;
	wdata->mp->id.vendor = wdata->hdev->vendor;
	wdata->mp->id.product = wdata->hdev->product;
	wdata->mp->id.version = wdata->hdev->version;
	wdata->mp->name = WIIMOTE_NAME " Motion Plus";

	set_bit(EV_ABS, wdata->mp->evbit);
	set_bit(ABS_RX, wdata->mp->absbit);
	set_bit(ABS_RY, wdata->mp->absbit);
	set_bit(ABS_RZ, wdata->mp->absbit);
	input_set_abs_params(wdata->mp,
			     ABS_RX, -16000, 16000, 4, 8);
	input_set_abs_params(wdata->mp,
			     ABS_RY, -16000, 16000, 4, 8);
	input_set_abs_params(wdata->mp,
			     ABS_RZ, -16000, 16000, 4, 8);

	ret = input_register_device(wdata->mp);
	if (ret)
		goto err_free;

	return 0;

err_free:
	input_free_device(wdata->mp);
	wdata->mp = NULL;
	return ret;
}
