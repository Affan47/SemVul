sd_stop0(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (sd->work_thread != NULL) {
		mutex_unlock(&gspca_dev->usb_lock);
		destroy_workqueue(sd->work_thread);
		mutex_lock(&gspca_dev->usb_lock);
		sd->work_thread = NULL;
	}
	if (!gspca_dev->present)
		return;
	send_unknown(gspca_dev, sd->sensor);
}
