rtl2832_sdr_start_streaming(struct vb2_queue *vq, unsigned int count)
{
	struct rtl2832_sdr_dev *dev = vb2_get_drv_priv(vq);
	struct platform_device *pdev = dev->pdev;
	struct rtl2832_sdr_platform_data *pdata = pdev->dev.platform_data;
	struct dvb_usb_device *d = pdata->dvb_usb_device;
	int ret;

	dev_dbg(&pdev->dev, "\n");

	if (!dev->udev)
		return -ENODEV;

	if (mutex_lock_interruptible(&dev->v4l2_lock))
		return -ERESTARTSYS;

	if (d->props->power_ctrl)
		d->props->power_ctrl(d, 1);


	if (d->props->frontend_ctrl)
		d->props->frontend_ctrl(pdata->dvb_frontend, 1);

	set_bit(POWER_ON, &dev->flags);


	if (V4L2_SUBDEV_HAS_OP(dev->v4l2_subdev, core, s_power))
		ret = v4l2_subdev_call(dev->v4l2_subdev, core, s_power, 1);
	else
		ret = rtl2832_sdr_set_tuner(dev);
	if (ret)
		goto err;

	ret = rtl2832_sdr_set_tuner_freq(dev);
	if (ret)
		goto err;

	ret = rtl2832_sdr_set_adc(dev);
	if (ret)
		goto err;

	ret = rtl2832_sdr_alloc_stream_bufs(dev);
	if (ret)
		goto err;

	ret = rtl2832_sdr_alloc_urbs(dev);
	if (ret)
		goto err;

	dev->sequence = 0;

	ret = rtl2832_sdr_submit_urbs(dev);
	if (ret)
		goto err;

err:
	mutex_unlock(&dev->v4l2_lock);

	return ret;
}
