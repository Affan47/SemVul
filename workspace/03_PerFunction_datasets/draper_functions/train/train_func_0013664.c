usb_stor_release_resources(struct us_data *us)
{


	usb_stor_dbg(us, "-- sending exit command to thread\n");
	complete(&us->cmnd_ready);
	if (us->ctl_thread)
		kthread_stop(us->ctl_thread);


	if (us->extra_destructor) {
		usb_stor_dbg(us, "-- calling extra_destructor()\n");
		us->extra_destructor(us->extra);
	}


	kfree(us->extra);
	usb_free_urb(us->current_urb);
}
