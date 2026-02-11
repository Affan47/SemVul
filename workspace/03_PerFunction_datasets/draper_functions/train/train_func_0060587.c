pvr2_ctl_timeout(unsigned long data)
{
	struct pvr2_hdw *hdw = (struct pvr2_hdw *)data;
	if (hdw->ctl_write_pend_flag || hdw->ctl_read_pend_flag) {
		hdw->ctl_timeout_flag = !0;
		if (hdw->ctl_write_pend_flag)
			usb_unlink_urb(hdw->ctl_write_urb);
		if (hdw->ctl_read_pend_flag)
			usb_unlink_urb(hdw->ctl_read_urb);
	}
}
