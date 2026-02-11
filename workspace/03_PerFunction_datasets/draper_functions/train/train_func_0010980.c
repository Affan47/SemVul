rtl2832_sdr_stop_streaming(struct vb2_queue *vq)
{
	struct rtl2832_sdr_dev *dev = vb2_get_drv_priv(vq);
	struct platform_device *pdev = dev->pdev;
	struct rtl2832_sdr_platform_data *pdata = pdev->dev.platform_data;
	struct dvb_usb_device *d = pdata->dvb_usb_device;

	dev_dbg(&pdev->dev, "\n");

	mutex_lock(&dev->v4l2_lock);

	rtl2832_sdr_kill_urbs(dev);
	rtl2832_sdr_free_urbs(dev);
	rtl2832_sdr_free_stream_bufs(dev);
	rtl2832_sdr_cleanup_queued_bufs(dev);
	rtl2832_sdr_unset_adc(dev);


	if (V4L2_SUBDEV_HAS_OP(dev->v4l2_subdev, core, s_power))
		v4l2_subdev_call(dev->v4l2_subdev, core, s_power, 0);
	else
		rtl2832_sdr_unset_tuner(dev);

	clear_bit(POWER_ON, &dev->flags);


	if (d->props->frontend_ctrl)
		d->props->frontend_ctrl(pdata->dvb_frontend, 0);

	if (d->props->power_ctrl)
		d->props->power_ctrl(d, 0);

	mutex_unlock(&dev->v4l2_lock);
}
