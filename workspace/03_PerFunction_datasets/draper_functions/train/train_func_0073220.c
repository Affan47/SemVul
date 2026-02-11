cx23885_vbi_irq(struct cx23885_dev *dev, u32 status)
{
	u32 count;
	int handled = 0;

	if (status & VID_BC_MSK_VBI_RISCI1) {
		dprintk(1, "%s() VID_BC_MSK_VBI_RISCI1\n", __func__);
		spin_lock(&dev->slock);
		count = cx_read(VID_A_GPCNT);
		cx23885_video_wakeup(dev, &dev->vbiq, count);
		spin_unlock(&dev->slock);
		handled++;
	}

	return handled;
}
