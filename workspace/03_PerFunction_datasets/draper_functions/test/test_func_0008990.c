mdc800_usb_waitForIRQ (int mode, int msec)
{
	mdc800->camera_request_ready=1+mode;

	wait_event_timeout(mdc800->irq_wait, mdc800->irq_woken,
			   msecs_to_jiffies(msec));
	mdc800->irq_woken = 0;

	if (mdc800->camera_request_ready>0)
	{
		mdc800->camera_request_ready=0;
		dev_err(&mdc800->dev->dev, "timeout waiting for camera.\n");
		return -1;
	}

	if (mdc800->state == NOT_CONNECTED)
	{
		printk(KERN_WARNING "mdc800: Camera gets disconnected "
		       "during waiting for irq.\n");
		mdc800->camera_request_ready=0;
		return -2;
	}

	return 0;
}
